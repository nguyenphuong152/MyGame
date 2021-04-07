#pragma once
#include "MarioOnAirStates.h"

class CMarioStateDrop : public CMarioOnAirStates
{
public:
	static CMarioStateDrop* __instance;

	CMarioStateDrop();
	virtual ~CMarioStateDrop() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateDrop* GetInstance();

};