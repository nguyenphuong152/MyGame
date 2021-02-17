#pragma once
#include "MarioState.h"

class CMarioOnGroundStates : public CMarioState
{
public:
	static CMarioOnGroundStates* __instance;

	CMarioOnGroundStates();
	virtual ~CMarioOnGroundStates() {};

	virtual void HandleInput(CMario& mario);
	virtual void Enter(CMario& mario) {};
	virtual void Update(DWORD dt, CMario& mario) {};
};
