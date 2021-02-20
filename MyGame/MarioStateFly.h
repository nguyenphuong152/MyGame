#pragma once
#include "MarioOnAirStates.h"

class CMarioStateFly : public CMarioOnAirStates
{
public:
	static CMarioStateFly* __instance;

	CMarioStateFly();
	virtual ~CMarioStateFly() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateFly* GetInstance();

};