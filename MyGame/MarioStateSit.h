#pragma once
#include "MarioOnGroundStates.h"

#define SIT_JUMP_Y 0.15f
#define MARIO_JUMP_TIME 250

class CMarioStateSit : public CMarioOnGroundStates
{
private:
	ULONGLONG _jumpingStart;
public:
	static CMarioStateSit* __instance;

	CMarioStateSit();
	virtual ~CMarioStateSit() {};

	void StartJumping() { _jumpingStart = GetTickCount64(); };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	void SetPositionAferSitting(CMario& mario);
	void SetPositionBeforeSitting(CMario& mario);
	static CMarioStateSit* GetInstance();

};