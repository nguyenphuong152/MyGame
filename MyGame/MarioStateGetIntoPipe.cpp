#include "MarioStateGetIntoPipe.h"
#include "MarioStateIdle.h"
#include "MarioStateJump.h"
#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "Camera.h"

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::__instance = NULL;

CMarioStateGetIntoPipe::CMarioStateGetIntoPipe() {
	DebugOut(L"[STATE] create go to pipe \n");
}

void CMarioStateGetIntoPipe::Enter(CMario& mario)
{
	mario.vx = 0;
	if (isTouchHiddenPipe) mario.SetAnimation(MARIO_ANI_DROP_FROP_PIPE);
    else mario.SetAnimation(MARIO_ANI_GET_INTO_PIPE);
}

void CMarioStateGetIntoPipe::HandleInput(CMario& mario, Input input)
{

}

void CMarioStateGetIntoPipe::Update(DWORD dt, CMario& mario)
{

	if (isUp)
	{
		mario.vy = -MARIO_IN_PIPE_VELOCITY_Y;
		//set lại vị trí cũ sau khi mario đã chui ra khỏi ống
			if (mario.y < position_out_y - MARIO_RACOON_BBOX_HEIGHT-18)
			{
				mario.SetPosition(mario.x, position_out_y - MARIO_RACOON_BBOX_HEIGHT);
				Reset();
				mario.ChangeState(CMarioState::idle.GetInstance());
			} //kiểm tra vị trí để chuyển cam ra khỏi hidden scene
			else if (inPipe == 1 && mario.y < position_toggle_cam_y)
			{
				inPipe = 0;
				CCamera::GetInstance()->GoBackToNormal();
				mario.SetPosition(POSITION_PLAYER_OUT_PIPE_X, POSITION_PLAYER_OUT_PIPE_Y);
			}
	}
	else {
		if (inPipe==1 && mario.y > position_toggle_cam_y)
		{
			inPipe = 0;
			CCamera::GetInstance()->AdjustPositionToHiddenScene();
			mario.SetPosition(HIDDEN_SCENE_X + 420, HIDDEN_SCENE_Y + 5);
		}
		mario.vy = MARIO_IN_PIPE_VELOCITY_Y;
	}
	if (isTouchHiddenPipe) mario.vy = MARIO_IN_PIPE_VELOCITY_Y*4;
}

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateGetIntoPipe();
	return __instance;
}

void CMarioStateGetIntoPipe::Reset()
{
	isUp = isTouchHiddenPipe = false;
	position_out_x = position_out_y = 0;
	//position_toggle_cam_x = position_toggle_cam_y = 0;
}