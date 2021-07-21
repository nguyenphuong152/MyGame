#pragma once
#include "MarioOnGroundStates.h"

#define POSITION_PLAYER_OUT_PIPE_X_1 6910
#define POSITION_PLAYER_OUT_PIPE_Y_1 1180

#define POSITION_PLAYER_OUT_PIPE_X_3 6246
#define POSITION_PLAYER_OUT_PIPE_Y_3 80

#define POSITION_OUT_PIPE	1150



#define MARIO_IN_PIPE_VELOCITY_Y 0.2f
#define CHANGE_STATE_TIME	450

class CMarioStateGetIntoPipe : public CMarioOnGroundStates
{
private:
	ULONGLONG _changeStateStart =  0;


	int isInPipe = 0;
	ULONGLONG inPipeStart;

	
	void ResetInPipe() { isInPipe = inPipeStart = 0; };

	void HandleSecretScreen1_1(CMario &mario);
	void HandleSecretScreen1_3(CMario& mario);

public:
	int isChangeState = 0;

	bool isTouchHiddenPipe = false;
	bool isUp = false;
	int inPipe = 0;

	float position_toggle_cam_x, position_toggle_cam_y;
	float position_out_x, position_out_y;
	static CMarioStateGetIntoPipe* __instance;

	void StartChangeState() { _changeStateStart = GetTickCount64(); isChangeState = 1; };

	CMarioStateGetIntoPipe();
	virtual ~CMarioStateGetIntoPipe() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateGetIntoPipe* GetInstance();
	void SetPostionOut(float x, float y) { position_out_x = x; position_out_y = y; }
	void SetPositionChangeCam(float x, float y) { position_toggle_cam_x = x; position_toggle_cam_y = y; };
	void Reset();

	void StartInPipe() { isInPipe = 1; inPipeStart = GetTickCount64(); };
};
