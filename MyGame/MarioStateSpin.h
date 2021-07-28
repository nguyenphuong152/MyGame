#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_SPINNING_TIME 300

class CMarioStateSpin : public CMarioOnGroundStates
{
private:
	ULONGLONG _spinningStart;
public:
	static CMarioStateSpin* __instance;
	bool isAttack;

	CMarioStateSpin();
	virtual ~CMarioStateSpin() {};

	void StartSpinning() { _spinningStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateSpin* GetInstance();

};