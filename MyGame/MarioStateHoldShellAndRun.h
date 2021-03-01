#pragma once
#include "MarioHoldingShellStates.h"

class CMarioStateHoldShellAndRun : public CMarioHoldingShellStates
{
public:
	static CMarioStateHoldShellAndRun* __instance;

	CMarioStateHoldShellAndRun();
	virtual ~CMarioStateHoldShellAndRun() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStateHoldShellAndRun* GetInstance();

};