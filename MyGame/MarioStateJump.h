#pragma once
#include "MarioOnAirStates.h"
#define MARIO_JUMP_TIME 250

class CMarioStateJump : public CMarioOnAirStates
{
private:
	ULONGLONG _jumpingStart;
public:
	static CMarioStateJump* __instance;
	CMarioStateJump();
	virtual ~CMarioStateJump() {};

	void StartJumping() {  _jumpingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	
	static CMarioStateJump* GetInstance();

};