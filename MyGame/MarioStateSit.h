#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateSit : public CMarioOnGroundStates
{
public:
	static CMarioStateSit* __instance;

	CMarioStateSit();
	virtual ~CMarioStateSit() {};

	virtual void HandleInput(CMario& mario);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateSit* GetInstance();

};