#pragma once
#pragma once
#include "MarioHoldingShellStates.h"

class CMarioStateHoldShellAndRun : public CMarioHoldingShellStates
{
public:
	static CMarioStateHoldShellAndRun* __instance;

	float NewTime = 0;
	float OldTime = 0;
	float deltaTime = 0;
	float power = 0;

	CMarioStateHoldShellAndRun();
	virtual ~CMarioStateHoldShellAndRun() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStateHoldShellAndRun* GetInstance();

};