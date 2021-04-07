#pragma once
#include "MarioOnGroundStates.h"

#define SIT_JUMP_VELOCITY_Y 0.2
#define SIT_DROP_VELOCITY_Y 0.007
#define TIME_TOGGLE_HIGH_JUMP_WHEN_SITTING 20
#define TIME_TURN_OFF_HIGH_JUMP 270

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