#pragma once
#include "MiniGoomba.h"

class CMiniGoombaPool
{
	friend class CPlayScene;
	static const int POOL_SIZE = 8;

	int ani_set = -1;

	CMiniGoomba* minigoombas[POOL_SIZE];
	CMiniGoomba* _firstAvailable;

public:
	static CMiniGoombaPool* __instance;
	CMiniGoombaPool();
	CMiniGoomba* Create();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void Init(vector<LPGAMEOBJECT>& objects, int ani);

	void SetMiniGoombaAnimation(int ani) { this->ani_set = ani; };
	void Unload();

	static CMiniGoombaPool* GetInstance();
};