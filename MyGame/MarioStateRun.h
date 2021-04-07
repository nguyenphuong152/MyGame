#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateRun : public CMarioOnGroundStates
{
public:
	static CMarioStateRun* __instance;

	float NewTime = 0;
	float OldTime = 0;
	float deltaTime = 0;
	float power = 0;

	CMarioStateRun();
	virtual ~CMarioStateRun() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStateRun* GetInstance();

};