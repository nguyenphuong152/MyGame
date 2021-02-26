#pragma once
#include "MarioHoldingShellStates.h"

class CMarioStateHoldShellIdle : public CMarioHoldingShellStates
{
public:
	static CMarioStateHoldShellIdle* __instance;

	CMarioStateHoldShellIdle();
	virtual ~CMarioStateHoldShellIdle() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	static CMarioStateHoldShellIdle* GetInstance();

};