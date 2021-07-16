#pragma once

#include "Scene.h"
#include "GameObject.h"
#include "Brick.h"
#include "Mario.h"
#include "Goomba.h"
#include "Koopas.h"
#include "Map.h"
#include "Ground.h"
#include "Coin.h"
#include "RedVenusFireTrap.h"
#include "FireBall.h"
#include "MapObjects.h"
#include "HUD.h"
#include "Text.h"
#include "Unit.h"



class CPlayScene : public CScene
{
protected:
	//create player for play scene
	CMario* player;
	Grid* grid;

	CMap* map;
	CMapObjects* map_objects;

	HUD* hud;
	Letter* letters;

	vector<LPGAMEOBJECT> objects;
	vector<LPGAMEOBJECT> coObjects;

	void _ParseSection_TEXTURES(string line);
	void _ParseSection_SPRITES(string line);
	void _ParseSection_ANIMATIONS(string line);
	void _ParseSection_ANIMATION_SETS(string line);
	void _ParseSection_OBJECTS(string line);
	void _ParseSection_MAP(string line);
	void _ParseSection_HUD(string line);
	void _ParseSection_LETTERS(string line);
	void _ParseSection_GRID(string line);

	//void AddObjectToGrid();

	void UpdatePool(vector<LPGAMEOBJECT>* cobjects, DWORD dt);
	void RenderPool();
	void UnloadPool();

public:
	CPlayScene(int id, LPCWSTR filePath);

	virtual void Load();
	virtual void Update(DWORD dt);
	virtual void Render();
	virtual void Unload();

	CMario* GetPlayer() { return player; }
	//friend class CPlayScenceKeyHandler;
};

class CPlaySceneKeyHandler : public CSceneKeyHandler
{
public:
	virtual void KeyState(BYTE* states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode) ;
	CPlaySceneKeyHandler(CScene* s) : CSceneKeyHandler(s) {};
};

