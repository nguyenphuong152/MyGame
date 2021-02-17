#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateWalk : public CMarioOnGroundStates
{
public:
	static CMarioStateWalk* __instance;

	CMarioStateWalk();
	virtual ~CMarioStateWalk() {};

	virtual void HandleInput(CMario& mario);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateWalk* GetInstance();

};