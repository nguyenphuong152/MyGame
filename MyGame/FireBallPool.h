#pragma once
#include "FireballTest.h"

class CFireBallPool 
{
	friend class CPlayScene;

	static const int POOL_SIZE = 3;
	CFireballTest fireballs[POOL_SIZE];
	CFireballTest* _firstAvailable;
public:
	CFireBallPool();
	void Create(float x, float y);
	void Update();
};