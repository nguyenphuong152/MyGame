#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateGetIntoPipe : public CMarioOnGroundStates
{
public:
	bool isTouchHiddenPipe = false;
	bool pipeDown = false;
	static CMarioStateGetIntoPipe* __instance;

	CMarioStateGetIntoPipe();
	virtual ~CMarioStateGetIntoPipe() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateGetIntoPipe* GetInstance();

};
