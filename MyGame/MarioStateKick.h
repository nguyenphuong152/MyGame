#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_KICKING_TIME 400

class CMarioStateKick : public CMarioOnGroundStates
{
private:
	ULONGLONG _kickingStart;
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