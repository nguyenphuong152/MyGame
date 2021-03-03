#pragma once
#include "FireballTest.h"

class CFireBallPool 
{
	static const int POOL_SIZE = 1;
	CFireballTest fireballs[POOL_SIZE];
	CFireballTest* _firstAvailable;
public:
	CFireBallPool();
	CFireballTest* Create();
	void Update();
};