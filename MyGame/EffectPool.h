#pragma once
#include "Effect.h"

class CEffectPool
{
	friend class CPlayScene;

	int ani_set = -1;

	static const int POOL_SIZE = 80;
	CEffect *effects[POOL_SIZE];
	CEffect* _firstAvailable;
	
public:
	static CEffectPool* __instance;
	CEffectPool();
	CEffect* Create();
	void SetEffectAnimation(int ani) { this->ani_set = ani; };

	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	void Render();

	void Init(vector<LPGAMEOBJECT> &objects,int ani);

	void Unload();

	static CEffectPool* GetInstance();
};