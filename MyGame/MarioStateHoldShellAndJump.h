#pragma once
#include "MarioHoldingShellStates.h"

#define AVERAGE_TIME_JUMP 100
#define MAX_TIME_JUMP 200

class CMarioStateHoldShellAndJump : public CMarioHoldingShellStates
{
public:
	static CMarioStateHoldShellAndJump* __instance;
	CMarioStateHoldShellAndJump();
	virtual ~CMarioStateHoldShellAndJump() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);


	static CMarioStateHoldShellAndJump* GetInstance();

};