#pragma once
#include "Fireball.h"

class CFireBallPool 
{
	friend class CPlayScene;
	static const int POOL_SIZE = 5;

	int ani_set = -1;

	CFireball *fireballs[POOL_SIZE];
	CFireball* _firstAvailable;

public:
	static CFireBallPool* __instance;
	CFireBallPool();
	CFireball* Create();
	void Update();
	void Init(vector<LPGAMEOBJECT> &objects);

	void SetFireballAnimation(int ani) { this->ani_set = ani; };

	static CFireBallPool* GetInstance();
};