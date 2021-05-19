#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateGetIntoPipe : public CMarioOnGroundStates
{
public:
	bool isTouchHiddenPipe = false;
	bool isUp = false;
	float position_out_x, position_out_y;
	static CMarioStateGetIntoPipe* __instance;

	CMarioStateGetIntoPipe();
	virtual ~CMarioStateGetIntoPipe() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateGetIntoPipe* GetInstance();
	void SetPostionOut(float x, float y) { position_out_x = x; position_out_y = y; }
	void ResetFlag() { isUp = false; isTouchHiddenPipe = false; }
};
