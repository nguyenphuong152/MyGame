#pragma once
#include "MarioOnGroundStates.h"
#define MARIO_SPINNING_TIME 20

class CMarioStateSpin : public CMarioOnGroundStates
{
private:
	int _spinningTime;
public:
	static CMarioStateSpin* __instance;

	int spinnable;
	DWORD spinning_start;

	CMarioStateSpin();
	virtual ~CMarioStateSpin() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateSpin* GetInstance();

};