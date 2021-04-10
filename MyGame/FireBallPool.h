#pragma once
#include "Fireball.h"

class CFireBallPool 
{
	friend class CPlayScene;

	static const int POOL_SIZE = 2;
	CFireball fireballs[POOL_SIZE];
	CFireball* _firstAvailable;
	CMario* player;
public:
	static CFireBallPool* __instance;
	CFireBallPool();
	void Create(float x, float y,bool isShootingUp, CMario* mario);
	void Update();

	static CFireBallPool* GetInstance();
};