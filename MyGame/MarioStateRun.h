#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateRun : public CMarioOnGroundStates
{
public:
	bool decreasePower;
	static CMarioStateRun* __instance;

	CMarioStateRun();
	virtual ~CMarioStateRun() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStateRun* GetInstance();

};