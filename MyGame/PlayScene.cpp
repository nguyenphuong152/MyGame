﻿#include "PlayScene.h"
#include <iostream>
#include <fstream>
#include "Textures.h"
#include "Sprites.h"
#include "Portal.h"
#include "Pipe.h"
#include "Animations.h"
#include "Game.h"
#include "Items.h"
#include "MarioState.h"
#include "Fireball.h"
#include "Camera.h"


using namespace std;

CPlayScene::CPlayScene(int id, LPCWSTR filePath) : CScene(id, filePath)
{
	key_handler = new CPlaySceneKeyHandler(this);
}

/*
	Load scene resources from scene file (textures, sprites, animations and objects)
	See scene1.txt, scene2.txt for detail format specification
*/

#define SCENE_SECTION_UNKNOWN -1
#define SCENE_SECTION_TEXTURES 2
#define SCENE_SECTION_SPRITES 3
#define SCENE_SECTION_ANIMATIONS 4
#define SCENE_SECTION_ANIMATION_SETS	5
#define SCENE_SECTION_OBJECTS	6
#define SCENE_SECTION_MAP	7

#define OBJECT_TYPE_MARIO	0
#define OBJECT_TYPE_BRICK	1
#define OBJECT_TYPE_GOOMBA	2
#define TRAP_RED_VENUS 5
#define ENEMY_KOOPAS	4 
#define OBJECT_TYPE_FIREBALL 3

#define OBJECT_TYPE_GROUND 60
#define OBJECT_TYPE_BOX 70
#define OBJECT_TYPE_PIPE 80
#define OBJECT_TYPE_PORTAL	50

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
		if (player != NULL)
		{
			DebugOut(L"[ERROR] MARIO object was created before!\n");
			return;
		}
		obj = CMario::GetInstance();
		obj->SetPosition(x, y);
		player = (CMario*)obj;

		DebugOut(L"[INFO] Player object created!\n");
		break;
	/*case TRAP_RED_VENUS:
	{
		obj = new CRedVenusFireTrap(player,pool);

	} break;*/
	case OBJECT_TYPE_FIREBALL:
	{
		pool = CFireBallPool::GetInstance();
		for (int i = 0; i <pool->POOL_SIZE ; i++)
		{
			objects.push_back(&pool->fireballs[i]);
		}
	} break;
	/*case OBJECT_TYPE_PIPE:
	{
		int spritePipe = atof(tokens[4].c_str());
		obj = new CPipe(spritePipe);
	}
	break;*/
	/*case OBJECT_TYPE_PORTAL:
	{
		float r = atof(tokens[4].c_str());
		float b = atof(tokens[5].c_str());
		int scene_id = atoi(tokens[6].c_str());
		obj = new CPortal(x, y, r, b, scene_id);
	}
	break;*/
	default:
		DebugOut(L"[ERR] Invalid object type: %d\n", object_type);
		return;
	}

	// General object setup
	if (object_type != OBJECT_TYPE_FIREBALL)
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

	CMap::GetInstance()->AddMap(id, &path[0],textureId, tilePerRow, tilePerColumn);
	CMap::GetInstance()->CreateTileSet();
	CMap::GetInstance()->HandleMap();
	CMap::GetInstance()->HandleObjectInMap(objects);
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
		}
	}

	f.close();

	CCamera::GetInstance()->SetPlayer(player);
	CTextures::GetInstance()->Add(ID_TEX_BBOX, L"textures\\bbox.png", D3DCOLOR_XRGB(255, 255, 255));
	DebugOut(L"[INFO] Done loading scene resources %s\n", sceneFilePath);
}



void CPlayScene::Update(DWORD dt)
{
	vector<LPGAMEOBJECT> coObjects;

	for (size_t i = 1; i < objects.size(); i++)
	{
		/*if (dynamic_cast<CFireballTest*>(objects[i])) {
			if (objects[i]->isEnable)
			{
				DebugOut(L"vi tri %d \n", i);
			}
		}*/
		if (objects[i]->isEnable)
		{
			coObjects.push_back(objects[i]);
		}
	}

	//player->CheckCollisionWithItems(&listItems);
	for (size_t i = 0; i < objects.size(); i++)
	{
		if (objects[i]->isEnable)
		{
			objects[i]->Update(dt, &coObjects);
		}
	}

	CFireBallPool::GetInstance()->Update();

	// skip the rest if scene was already unloaded (Mario::Update might trigger PlayScene::Unload)
	if (player == NULL) return;
}

void CPlayScene::Render()
{
	CMap::GetInstance()->RenderMap();
	for (int i = 1; i < objects.size(); i++)
	{
		objects[i]->Render();
	}
	//render mario sau cung
	objects[0]->Render();
		
}

/*
unload current scene
*/

void CPlayScene::Unload()
{
	for (int i = 0; i < objects.size(); i++)
		delete objects[i];

	objects.clear();
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
		mario->Die();
		break;
	case DIK_A:
		input = Input::PRESS_A;
		mario->HandleInput(input);
		mario->powerMode = true;
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