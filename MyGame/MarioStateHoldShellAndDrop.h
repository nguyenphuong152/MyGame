#pragma once
#include "MarioStateHoldShellAndJump.h"

class CMarioStateHoldShellAndDrop : public CMarioStateHoldShellAndJump
{
public:
	static CMarioStateHoldShellAndDrop* __instance;

	CMarioStateHoldShellAndDrop();
	virtual ~CMarioStateHoldShellAndDrop() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateHoldShellAndDrop* GetInstance();

};
