#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_KICKING_TIME 15

class CMarioStateKick : public CMarioOnGroundStates
{
private:
	int _kickingTime;
public:
	static CMarioStateKick* __instance;

	CMarioStateKick();
	virtual ~CMarioStateKick() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateKick* GetInstance();

};