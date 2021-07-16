#pragma once
#include "MarioStateJump.h"
#define MARIO_THROWING_TIME 200

class CMarioStateThrowFireballJumping : public CMarioStateJump
{
private:
	ULONGLONG _throwingStart;
public:
	static CMarioStateThrowFireballJumping* __instance;

	CMarioStateThrowFireballJumping();
	virtual ~CMarioStateThrowFireballJumping() {};

	void StartThrowing() { _throwingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateThrowFireballJumping* GetInstance();

};