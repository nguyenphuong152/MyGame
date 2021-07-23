#pragma once
#include "MarioState.h"

class CMarioOnAirStates : public CMarioState
{

public:
	static CMarioOnAirStates* __instance;

	CMarioOnAirStates();
	virtual ~CMarioOnAirStates() {};

	virtual void HandleInput(CMario& mario, Input input);
	void SetStateJumping( CMario& mario);
	virtual void Enter(CMario& mario) {};
	virtual void Update(DWORD dt, CMario& mario) {};

};
