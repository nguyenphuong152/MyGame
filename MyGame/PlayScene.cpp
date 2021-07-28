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
#include "Notification.h"
#include "IntroScene.h"

using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	player = NULL;
	grid = NULL;
    map = NULL;
	map_objects = NULL;
	hud = NULL;
	letters= NULL;
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
#define SCENE_SECTION_GRID				6
#define SCENE_SECTION_MAP				7
#define SCENE_SECTION_HUD				8
#define SCENE_SECTION_LETTERS			9
#define SCENE_SECTION_PLAYER_DATA		10


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
	for (UINT i = 1; i < tokens.size(); i += 2)	// why i+=2 ?  sprite_id | frame_time  
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

	for (UINT i = 1; i < tokens.size(); i++)
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
	if (tokens.size() < 3) return; // skip invalid lines - an object set must have at least id, x, y

	int object_type = atoi(tokens[0].c_str());
	double x = atof(tokens[1].c_str());
	double y = atof(tokens[2].c_str());  //to f

	int ani_set_id = atoi(tokens[3].c_str());

	CAnimationSets* animation_sets = CAnimationSets::GetInstance();

	CGameObject* obj = NULL;

	switch (object_type)
	{
	case OBJECT_TYPE_MARIO:
	{
		obj = new CMario((float)x,(float)y);
		obj->SetPosition((float)x, (float)y);
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
	{//
		obj->SetObjectAnimation(ani_set_id);
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
	
	map_objects = new CMapObjects(grid);
	map_objects->GenerateObject(&path[0], objects);

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

void CPlayScene::_ParseSection_LETTERS(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	string name = tokens[0].c_str();
	int texture = atoi(tokens[1].c_str());

	HUD::GetInstance()->AddLetter(name, texture);
}

void CPlayScene::_ParseSection_GRID(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 2) return;
	string path = tokens[1];

	grid->ReadFile(&path[0]);
}

void CPlayScene::_ParseSection_PLAYER_DATA(string line)
{
	vector<string> tokens = split(line);

	if (tokens.size() < 1) return;
	string path = tokens[0];

	string data;
	ifstream f;
	f.open(path);

	while (getline(f, data)) {
		vector<string> tokens = split(data);
		string property = tokens[0];
		if (property == "[LEVEL]")     player->SetLevel(atoi(tokens[1].c_str()));
		else if (property == "[COIN]") player->SetCoins(atoi(tokens[1].c_str()));
		else if (property == "[LIVE]") player->SetLive(atoi(tokens[1].c_str()));
		else if (property == "[POINT]") player->SetPoints(atoi(tokens[1].c_str()));
		else if (property == "[REWARD]")
		{
			player->SetReward(tokens[1]);
			HUD::GetInstance()->AddReward(tokens[1]);
		}
	}
	f.close();
	
}

void CPlayScene::Load()
{
	DebugOut(L"[INFO] Start loading scene resources from : %s \n", sceneFilePath);
	grid = new Grid();

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
		if (line == "[GRID]")
		{
			section = SCENE_SECTION_GRID; continue;
		}
		if (line == "[DATA]")
		{
			section = SCENE_SECTION_PLAYER_DATA; continue;
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
		case SCENE_SECTION_LETTERS:_ParseSection_LETTERS(line); break;
		case SCENE_SECTION_GRID:_ParseSection_GRID(line); break;
		case SCENE_SECTION_PLAYER_DATA: _ParseSection_PLAYER_DATA(line); break;
		}
	}

	f.close();

	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);

	if (CGame::GetInstance()->current_scene == INTRO)
	{
		IntroScene::GetInstance()->Init(objects, map);
		player = CGame::GetInstance()->GetPlayer();
	}
}



void CPlayScene::Update(DWORD dt)
{
	if (player == NULL) return;

	coObjects.clear();
	if (CGame::GetInstance()->current_scene == INTRO)
	{
		grid->Update(dt, &coObjects);
		IntroScene::GetInstance()->Update(dt, &coObjects);
	}
	else {
		// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
		grid->Update(dt, &coObjects);
		player->Update(dt, &coObjects);

		if (CNotification::GetInstance()->visible)
			CNotification::GetInstance()->Update();
	}
}

void CPlayScene::RenderPool()
{
	CFireBallPool::GetInstance()->Render();
	CEffectPool::GetInstance()->Render();
	CBoomerangPool::GetInstance()->Render();
	CMiniGoombaPool::GetInstance()->Render();
}


void CPlayScene::Render()
{
	if (player == NULL) return;
	if (CGame::GetInstance()->current_scene == INTRO)
	{
		IntroScene::GetInstance()->Render();
		grid->Render();
	}
	else {
		RenderPlayScene();
	}
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

void CPlayScene::RenderPlayScene()
{

	if (player->canWalkBehindMap == false)
	{
		map->RenderMap();
		grid->Render();
		player->Render();
	}
	else {
		player->Render();
		map->RenderMap();
		grid->Render();
	}

	if (CGame::GetInstance()->current_scene != OVERWORLD_MAP)
		map->RenderForeground();

	RenderPool();
	HUD::GetInstance()->Render();

	if (CNotification::GetInstance()->visible)
		CNotification::GetInstance()->Render();
}

void CPlayScene::Unload()
{
	for (size_t i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();

	delete grid;

	CGame::GetInstance()->DeleteCam();

	UnloadPool();

	map_objects = NULL;
	map = NULL;

	CGame::GetInstance()->DeletePlayer();

	player = NULL;

	DebugOut(L"[INFO] Scene %s unloaded! \n", sceneFilePath);
}

void CPlaySceneKeyHandler::IntroHandleKeyDown(int KeyCode)
{
	CArrow* arrow = IntroScene::GetInstance()->GetArrow();
	Input input = Input::NONE;
	switch (KeyCode)
	{
	case DIK_S:
		input = Input::PRESS_S;
		arrow->StartGame();
		break;
	case DIK_DOWN:
		input = Input::PRESS_DOWN;
		arrow->MoveDown();
		break;
	case DIK_UP:
		input = Input::PRESS_DOWN;
		arrow->MoveUp();
		break;
	}
}

void CPlaySceneKeyHandler::PlaySceneHandleKeyDown(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input = Input::NONE;
	switch (KeyCode)
	{
	case DIK_S:
		input = Input::PRESS_S;
		mario->canChangeMap = true;
		break;
	case DIK_DOWN:
		input = Input::PRESS_DOWN;
		break;
	case DIK_LEFT:
		input = Input::PRESS_LEFT;
		break;
	case DIK_RIGHT:
		input = Input::PRESS_RIGHT;
		break;
	case DIK_2:
		mario->ResetMario(MARIO_LEVEL_BIG);
		break;
	case DIK_1:
		mario->ResetMario(MARIO_LEVEL_SMALL);
		break;
	case DIK_3:
		mario->ResetMario(MARIO_LEVEL_RACOON);
		break;
	case DIK_4:
		mario->ResetMario(MARIO_LEVEL_FIRE);
		break;
	case DIK_5:
		mario->SetState(MARIO_STATE_DIE);
		break;
	case DIK_A:
		input = Input::PRESS_A;
		break;
	case DIK_6:
		mario->SwitchOverworld();
		break;
	case DIK_7:
		mario->MoveToSecretScreen();
		break;
	}
	mario->HandleInput(input);
}


void CPlaySceneKeyHandler::OnKeyDown(int KeyCode)
{
	if (CGame::GetInstance()->current_scene == INTRO)
		IntroHandleKeyDown(KeyCode);
	else  PlaySceneHandleKeyDown(KeyCode);
}

void CPlaySceneKeyHandler::OnKeyUp(int KeyCode)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	Input input = Input::NONE;

	if (CGame::GetInstance()->current_scene == INTRO)
		IntroScene::GetInstance()->GetSecondMario()->HandleInput(input);
	else {
		switch (KeyCode)
		{
		case DIK_LEFT:
			input = Input::RELEASE_LEFT;
			break;
		case DIK_RIGHT:
			input = Input::RELEASE_RIGHT;
			break;
		case DIK_DOWN:
			input = Input::RELEASE_DOWN;
			break;
		case DIK_S:
			input = Input::RELEASE_S;
			break;
		case DIK_A:
			input = Input::RELEASE_A;
			mario->powerMode = false;
			break;
		}
	}
	mario->HandleInput(input);
	
}

void CPlaySceneKeyHandler::KeyState(BYTE* states)
{
	CMario* mario = ((CPlayScene*)scene)->GetPlayer();
	 if (CGame::GetInstance()->current_scene != INTRO)
	 {
		 mario->HandleInput(Input::KEYSTATE);
	 }
}