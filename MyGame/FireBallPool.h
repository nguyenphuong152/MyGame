#pragma once
#include "FireballTest.h"

class CFireBallPool 
{
	friend class CPlayScene;

	static const int POOL_SIZE = 2;
	CFireballTest fireballs[POOL_SIZE];
	CFireballTest* _firstAvailable;
	CMario* player;
public:
	CFireBallPool(CMario *mario);
	void Create(float x, float y,bool isShootingUp);
	void Update();
};