#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateSit : public CMarioOnGroundStates
{
public:
	static CMarioStateSit* __instance;

	CMarioStateSit();
	virtual ~CMarioStateSit() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	void SetPositionAferSitting(CMario& mario);
	static CMarioStateSit* GetInstance();

};