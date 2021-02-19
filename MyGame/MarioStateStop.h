#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateStop : public CMarioOnGroundStates
{
public:
	static CMarioStateStop* __instance;

	CMarioStateStop();
	virtual ~CMarioStateStop() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);

	void CalculateSkidAcceleration(float acecelerate, DWORD dt, CMario& mario);
	static CMarioStateStop* GetInstance();

};