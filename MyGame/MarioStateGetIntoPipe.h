#pragma once
#include "MarioOnGroundStates.h"

#define POSITION_PLAYER_OUT_PIPE_X 6910
#define POSITION_PLAYER_OUT_PIPE_Y 1180

#define MARIO_IN_PIPE_VELOCITY_Y 0.2f

class CMarioStateGetIntoPipe : public CMarioOnGroundStates
{
public:
	bool isTouchHiddenPipe = false;
	bool isUp = false;
	int inPipe = 0;
	float position_toggle_cam_x, position_toggle_cam_y;
	float position_out_x, position_out_y;
	static CMarioStateGetIntoPipe* __instance;

	CMarioStateGetIntoPipe();
	virtual ~CMarioStateGetIntoPipe() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateGetIntoPipe* GetInstance();
	void SetPostionOut(float x, float y) { position_out_x = x; position_out_y = y; }
	void SetPositionChangeCam(float x, float y) { position_toggle_cam_x = x; position_toggle_cam_y = y; };
	void Reset();
};
