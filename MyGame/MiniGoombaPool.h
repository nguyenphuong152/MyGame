#pragma once
#include "MiniGoomba.h"

class CMiniGoombaPool
{
	friend class CPlayScene;
	static const int POOL_SIZE = 7;

	int ani_set = -1;

	CMiniGoomba* minigoombas[POOL_SIZE];
	CMiniGoomba* _firstAvailable;

public:
	static CMiniGoombaPool* __instance;
	CMiniGoombaPool();
	CMiniGoomba* Create();
	void Update();
	void Init(vector<LPGAMEOBJECT>& objects, int ani);

	void SetBoomerangAnimation(int ani) { this->ani_set = ani; };
	void Unload();

	static CMiniGoombaPool* GetInstance();
};