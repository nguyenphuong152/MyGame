#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_THROWING_TIME 100

class CMarioStateThrowFireball : public CMarioOnGroundStates
{
private:
	DWORD _throwingStart;
public:
	static CMarioStateThrowFireball* __instance;

	CMarioStateThrowFireball();
	virtual ~CMarioStateThrowFireball() {};

	void StartThrowing() { _throwingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateThrowFireball* GetInstance();

};