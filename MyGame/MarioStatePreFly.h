#pragma once

#include "MarioOnGroundStates.h"

class CMarioStatePreFly : public CMarioOnGroundStates
{
public:
	static CMarioStatePreFly* __instance;

	CMarioStatePreFly();
	virtual ~CMarioStatePreFly() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStatePreFly* GetInstance();

};