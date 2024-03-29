#pragma once
#include "Boomerang.h"

class CBoomerangPool
{
	friend class CPlayScene;
	static const int POOL_SIZE = 5;

	int ani_set = -1;

	CBoomerang* boomerangs[POOL_SIZE];
	CBoomerang* _firstAvailable;

public:
	static CBoomerangPool* __instance;
	CBoomerangPool();
	CBoomerang* Create();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();
	void Init(vector<LPGAMEOBJECT>& objects, int ani);

	void SetBoomerangAnimation(int ani) { this->ani_set = ani; };
	void Unload();

	static CBoomerangPool* GetInstance();
};