#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateSpin : public CMarioOnGroundStates
{
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