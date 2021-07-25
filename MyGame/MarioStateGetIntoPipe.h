#pragma once
#include "MarioOnGroundStates.h"

#define MARIO_IN_PIPE_VELOCITY_Y 0.4f
#define CHANGE_STATE_TIME	450
#define IN_PIPE_TIME 440
#define IN_PIPE_SHORT_TIME 80

#define UP -1
#define DOWN 1

class CMarioStateGetIntoPipe : public CMarioOnGroundStates
{
private:
	ULONGLONG _changeStateStart =  0;
	int isChangeState = 0;

	int isInPipe = 0;
	ULONGLONG inPipeStart;

	int isOutPipe = 0;
	ULONGLONG outPipeStart = 0;
	
	void ResetInPipe() { isInPipe = 0; inPipeStart = 0; };

	void StartChangeState() { _changeStateStart = GetTickCount64(); isChangeState = 1; };
	void ResetChangeState() { isChangeState = 0; _changeStateStart = 0; };

	void ResetOutPipe() { isOutPipe = 0; outPipeStart = 0; };

	void HandleSecretScreen1_1(CMario &mario);
	void HandleSecretScreen1_3(CMario& mario);

public:
	bool isTouchHiddenPipe = false;
	int dir = 1;

	static CMarioStateGetIntoPipe* __instance;

	CMarioStateGetIntoPipe();
	virtual ~CMarioStateGetIntoPipe() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateGetIntoPipe* GetInstance();

	void StartInPipe() { isInPipe = 1; inPipeStart = GetTickCount64(); };
	void StartOutPipe() { outPipeStart = GetTickCount64(); isOutPipe = 1; dir = UP; };
};
