#pragma once
#include "MarioOnGroundStates.h"

#define SIT_JUMP_Y 0.15f
#define MARIO_JUMP_TIME 250

#define SITTING_TIME 3000

class CMarioStateSit : public CMarioOnGroundStates
{
private:
	ULONGLONG _jumpingStart;

	ULONGLONG _prepareWalkBehindMapStart;
public:
	static CMarioStateSit* __instance;
	
	int preparing = 0;

	CMarioStateSit();
	virtual ~CMarioStateSit() {};

	void StartJumping() { _jumpingStart = GetTickCount64(); };
	void StartPrepair() { preparing = 1; _prepareWalkBehindMapStart = GetTickCount64(); };
	void ResetPrepair() { preparing = 0; _prepareWalkBehindMapStart = 0; };

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	void SetPositionAferSitting(CMario& mario);
	void SetPositionBeforeSitting(CMario& mario);
	static CMarioStateSit* GetInstance();

};