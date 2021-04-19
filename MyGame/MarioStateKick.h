#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_KICKING_TIME 200

class CMarioStateKick : public CMarioOnGroundStates
{
private:
	DWORD _kickingStart;
public:
	static CMarioStateKick* __instance;

	CMarioStateKick();
	virtual ~CMarioStateKick() {};

	void StartKicking() { _kickingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateKick* GetInstance();

};