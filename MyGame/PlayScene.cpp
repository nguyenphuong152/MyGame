#include "PlayScene.h"
#include <iostream>
#include <fstream>
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Pipe.h"
#include "Animations.h"
#include "Game.h"
#include "MarioState.h"
#include "Fireball.h"
#include "Camera.h"
#include "FireBallPool.h"
#include "MapObjects.h"
#include "EffectPool.h"
#include "HUD.h"
#include "MarioStateGetIntoPipe.h"
#include "MarioTail.h"
#include "PowerUp.h"
#include "BoomerangPool.h"
#include "MiniGoombaPool.h"
#include "Grid.h"
#include "Switch.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CPlaySceneKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN		-1
#define SCENE_SECTION_TEXTURES		 1
#define SCENE_SECTION_SPRITES		 2
#define SCENE_SECTION_ANIMATIONS		3
#define SCENE_SECTION_ANIMATION_SETS	4
#define SCENE_SECTION_OBJECTS			5
#define SCENE_SECTION_MAP				6
#define SCENE_SECTION_HUD				7
#define SCENE_SECTION_LETTERS			8

#define OBJECT_TYPE_MARIO		0
#define OBJECT_TYPE_FIREBALL	1
#define OBJECT_TYPE_EFFECT		2
#define OBJECT_TYPE_PORTAL		50
#define OBJECT_TYPE_TAIL		4
#define OBJECT_TYPE_BOOMERANG	3
#define OBJECT_TYPE_MINIGOOMBA	5

#define MAX_SCENE_LINE 2048


void CPlayScene::_ParseSection_TEXTURES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return; // skip invalid lines

	int texID = atoi(tokens[0].c_str());
	wstring path = ToWSTR(tokens[1]);
	int R = atoi(tokens[2].c_str());
	int G = atoi(tokens[3].c_str());
	int B = atoi(tokens[4].c_str());

	CTextures::GetInstance()->Add(texID, path.c_str(), D3DCOLOR_XRGB(R, G, B));
}

void CPlayScene::_ParseSection_SPRITES(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 6) return; // skip invalid lines

	int ID = atoi(tokens[0].c_str());
	int l = atoi(tokens[1].c_str());
	int t = atoi(tokens[2].c_str());
	int r = atoi(tokens[3].c_str());
	int b = atoi(tokens[4].c_str());
	int texID = atoi(tokens[5].c_str());

	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texID);
	if (tex == NULL)
	{
		DebugOut(L"[ERROR] Texture ID %d not found!\n", texID);
		return;
	}

	CSprites::GetInstance()->Add(ID, l, t, r, b, tex);
}

void CPlayScene::_ParseSection_ANIMATIONS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 3) return; // skip invalid lines - an animation must at least has 1 frame and 1 frame time
	LPANIMATION ani = new CAnimation();

	int ani_id = atoi(tokens[0].c_str());
	for (int i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
	{
		int sprite_id = atoi(tokens[i].c_str());
		int frame_time = atoi(tokens[i + 1].c_str());
		ani->Add(sprite_id, frame_time);
	}

	CAnimations::GetInstance()->Add(ani_id, ani);
}

void CPlayScene::_ParseSection_ANIMATION_SETS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return; // skip invalid lines - an animation set must at least id and one animation id

	int ani_set_id = atoi(tokens[0].c_str()); // to int

	LPANIMATION_SET s = new CAnimationSet();

	CAnimations* animations = CAnimations::GetInstance();

	for (int i = 1; i < tokens.size(); i++)
	{
		int ani_id = atoi(tokens[i].c_str());

		LPANIMATION ani = animations->Get(ani_id);
		s->push_back(ani);
	}

	CAnimationSets::GetInstance()->Add(ani_set_id, s);
}

/*
	Parse a line in section [OBJECTS]
*/
void CPlayScene::_ParseSection_OBJECTS(string line)
{
	vector<string> tokens = split(line);

	//DebugOut(L"--> %s\n",ToWSTR(line).c_str());

	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	float x = atof(tokens[1].c_str());
	float y = atof(tokens[2].c_str());  //to f

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = new CMario(x,y);
		obj->SetPosition(x, y);
		player = (CMario*)obj;
		CGame::GetInstance()->SetMainPlayer(player);

		DebugOut(L"[INFO] Player object created!\n");
	} break;
	case OBJECT_TYPE_FIREBALL:
	{
		CFireBallPool::GetInstance()->Init(objects,ani_set_id);
	} break;
	case OBJECT_TYPE_TAIL:
	{
		obj = new CMarioTail();
		obj->SetPosition((player->x+2)*player->nx, player->y+MARIO_RACOON_BBOX_HEIGHT+32);
		player->AttachTail((CMarioTail*)obj);
		objects.push_back(obj);
	} break;
	case OBJECT_TYPE_EFFECT:
	{
		CEffectPool::GetInstance()->Init(objects, ani_set_id);
	} break;
	case OBJECT_TYPE_BOOMERANG:
	{
		CBoomerangPool::GetInstance()->Init(objects, ani_set_id);
	} break;
	case OBJECT_TYPE_MINIGOOMBA:
	{
		CMiniGoombaPool::GetInstance()->Init(objects, ani_set_id);
	} break;
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (object_type == OBJECT_TYPE_MARIO)
	{
		obj->SetPosition(x, y);
		LPANIMATION_SET ani_set = animation_sets->Get(ani_set_id);

		obj->SetAnimationSet(ani_set);
		objects.push_back(obj);
	}
}

void CPlayScene::_ParseSection_MAP(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 5) return;
	int id = atoi(tokens[0].c_str());
	string path = tokens[1];

	int textureId = atoi(tokens[2].c_str());
	int tilePerRow = atoi(tokens[3].c_str());
	int tilePerColumn = atoi(tokens[4].c_str());

	map = new CMap(id, &path[0], textureId, tilePerRow, tilePerColumn);
	map->CreateTileSet();
	map->HandleMap();
	
	map_objects = new CMapObjects();
	map_objects->GenerateObject(&path[0], objects);

	AddObjectToGrid();
}

void CPlayScene::_ParseSection_HUD(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;
	int texture = atoi(tokens[0].c_str());
	float pos;

	if (CGame::GetInstance()->current_scene != OVERWORLD_MAP)
	{
		pos = HUD_POSITION_Y;
	}
	else {
		pos = HUD_POSITION_Y_OW;
	}
	
	HUD::GetInstance()->Init(texture, pos);
		
}

void CPlayScene::_ParseSection_Letters(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	string name = tokens[0].c_str();
	int texture = atoi(tokens[1].c_str());

	HUD::GetInstance()->AddLetter(name, texture);
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);

	ifstream f;
	f.open(sceneFilePath);

	// current resource section flag
	int section = SCENE_SECTION_UNKNOWN;

	char str[MAX_SCENE_LINE];
	while (f.getline(str, MAX_SCENE_LINE))
	{
		string line(str);

		if (line[0] == '#') continue;	// skip comment lines	

		if (line == "[TEXTURES]") { section = SCENE_SECTION_TEXTURES; continue; }
		if (line == "[SPRITES]") {
			section = SCENE_SECTION_SPRITES; continue;
		}
		if (line == "[ANIMATIONS]") {
			section = SCENE_SECTION_ANIMATIONS; continue;
		}
		if (line == "[ANIMATION_SETS]") {
			section = SCENE_SECTION_ANIMATION_SETS; continue;
		}
		if (line == "[OBJECTS]") {
			section = SCENE_SECTION_OBJECTS; continue;
		}
		if (line == "[MAP]") {
			section = SCENE_SECTION_MAP; continue;
		}
		if (line == "[FONT]")
		{
			section = SCENE_SECTION_LETTERS; continue;
		}
		if (line == "[HUD]")
		{
			section = SCENE_SECTION_HUD; continue;
		}

		if (line[0] == '[') { section = SCENE_SECTION_UNKNOWN; continue; }

		//
		// data section
		//
		switch (section)
		{
		case SCENE_SECTION_TEXTURES: _ParseSection_TEXTURES(line); break;
		case SCENE_SECTION_SPRITES: _ParseSection_SPRITES(line); break;
		case SCENE_SECTION_ANIMATIONS: _ParseSection_ANIMATIONS(line); break;
		case SCENE_SECTION_ANIMATION_SETS: _ParseSection_ANIMATION_SETS(line); break;
		case SCENE_SECTION_OBJECTS: _ParseSection_OBJECTS(line); break;
		case SCENE_SECTION_MAP: _ParseSection_MAP(line); break;
		case SCENE_SECTION_HUD: _ParseSection_HUD(line); break;
		case SCENE_SECTION_LETTERS:_ParseSection_Letters(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	
	//DebugOut(L"[OBJECT SIZE] %d \n", objects.size());
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}


void CPlayScene::Update(DWORD dt)
{
	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;

	coObjects.clear();

	grid->GetUnitsFromCameraRegion(&coObjects);
	grid->Update(dt, &coObjects);

	UpdatePool(&coObjects,dt);

	player->Update(dt, &coObjects);

	CGame::GetInstance()->GetMainCamera()->Update(dt, &coObjects);

	HUD::GetInstance()->Update();
}

void CPlayScene::RenderPool()
{
	CFireBallPool::GetInstance()->Render();
	CEffectPool::GetInstance()->Render();
	CBoomerangPool::GetInstance()->Render();
	CMiniGoombaPool::GetInstance()->Render();
}

void CPlayScene::AddObjectToGrid()
{
	grid = new Grid();
	for (size_t i = 1; i < objects.size(); i++)
	{
		if (dynamic_cast<CCamera*>(objects[i]) == false||dynamic_cast<CMarioTail*>(objects[i])== false) {
			objects[i]->AddObjectToGrid(grid);
		}
	}
}

void CPlayScene::UpdatePool(vector<LPGAMEOBJECT>* cobjects, DWORD dt)
{
	CFireBallPool::GetInstance()->Update(dt,cobjects);
	CEffectPool::GetInstance()->Update(dt,cobjects);
	CBoomerangPool::GetInstance()->Update(dt, cobjects);
	CMiniGoombaPool::GetInstance()->Update(dt, cobjects);
}


void CPlayScene::Render()
{
	if (player == NULL) return;

	map->RenderMap();

	RenderPool();

	grid->Render();

	player->Render();

	if(CGame::GetInstance()->current_scene != OVERWORLD_MAP)
	{
		map->RenderForeground();
	}

	HUD::GetInstance()->Render();
}

/*
unload current scene
*/
void CPlayScene::UnloadPool()
{
	CFireBallPool::GetInstance()->Unload();
	CEffectPool::GetInstance()->Unload();
	CBoomerangPool::GetInstance()->Unload();
	CMiniGoombaPool::GetInstance()->Unload();
}

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (dynamic_cast<CCamera*>(objects[i])) continue;
		delete objects[i];
	}

	objects.clear();
	
	HUD::GetInstance()->Unload();

	UnloadPool();

	map_objects = NULL;
	map = NULL;

	CGame::GetInstance()->DeletePlayer();

	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}


void CPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input;
	switch (KeyCode)
	{
	case DIK_S:
		input = Input::PRESS_S;
		mario->HandleInput(input);
		mario->canChangeMap = true;
		break;
	case DIK_DOWN:
		input = Input::PRESS_DOWN;
		mario->HandleInput(input);
		break;
	case DIK_LEFT:
		input = Input::PRESS_LEFT;
		mario->HandleInput(input);
		break;
	case DIK_RIGHT:
		input = Input::PRESS_RIGHT;
		mario->HandleInput(input);
		break;
	case DIK_2:
		mario->BigMario();
		break;
	case DIK_1:
		mario->RaccoonMario();
		break;
	case DIK_3:
		mario->FireMario();
		break;
	case DIK_4:
		mario->ImmortalMario();
		break;
	case DIK_5:
		mario->Die();
		break;
	case DIK_A:
		input = Input::PRESS_A;
		mario->HandleInput(input);
		break;
	case DIK_6 :
		mario->SwitchOverworld();
		break;
	}
}

void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input;
	switch (KeyCode)
	{
	case DIK_LEFT:
		input = Input::RELEASE_LEFT;
		mario->HandleInput(input);
		break;
	case DIK_RIGHT:
		input = Input::RELEASE_RIGHT;
		mario->HandleInput(input);
		break;
	case DIK_DOWN:
		input = Input::RELEASE_DOWN;
		mario->HandleInput(input);
		break;
	case DIK_S:
		input = Input::RELEASE_S;
		mario->HandleInput(input);
		break;
	case DIK_A:
		input = Input::RELEASE_A;
		mario->HandleInput(input);
		mario->powerMode = false;
		break;
	}
}

void CPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	mario->HandleInput(Input::KEYSTATE);
}