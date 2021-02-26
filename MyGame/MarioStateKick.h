#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateKick : public CMarioOnGroundStates
{
public:
	static CMarioStateKick* __instance;

	CMarioStateKick();
	virtual ~CMarioStateKick() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateKick* GetInstance();

};