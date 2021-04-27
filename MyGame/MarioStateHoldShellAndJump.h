#pragma once
#include "MarioHoldingShellStates.h"

#define MARIO_JUMP_TIME 250

class CMarioStateHoldShellAndJump : public CMarioHoldingShellStates
{
private:
	DWORD _jumpingStart;
public:
	static CMarioStateHoldShellAndJump* __instance;
	CMarioStateHoldShellAndJump();
	virtual ~CMarioStateHoldShellAndJump() {};

	void StartJumping() { _jumpingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);


	static CMarioStateHoldShellAndJump* GetInstance();

};