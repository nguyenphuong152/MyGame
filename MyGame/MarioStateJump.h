#pragma once
#include "MarioOnAirStates.h"

class CMarioStateJump : public CMarioOnAirStates
{
public:
	static CMarioStateJump* __instance;

	CMarioStateJump();
	virtual ~CMarioStateJump() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateJump* GetInstance();

};