#pragma once
#include "MarioState.h"
#define MARIO_SPEED 0.3f


class CMarioOnGroundStates : public CMarioState
{

public:
	static CMarioOnGroundStates* __instance;

	CMarioOnGroundStates();
	virtual ~CMarioOnGroundStates() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario) {};
	virtual void Update(DWORD dt, CMario& mario) {};

	void SetStateWalking(int direction, CMario& mario);
	void SetStateRunning(int direction, CMario& mario);
	void SetStateJumping(float jumpSpeed, CMario& mario);
};
