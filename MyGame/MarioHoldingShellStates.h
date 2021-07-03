#pragma once
#include "MarioState.h"


class CMarioHoldingShellStates : public CMarioState
{
public:
	static CMarioHoldingShellStates* __instance;

	CMarioHoldingShellStates();
	virtual ~CMarioHoldingShellStates() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario) {};
	virtual void Update(DWORD dt, CMario& mario) {};

};
