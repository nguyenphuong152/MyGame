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
	if (GetTickCount64() - _changeStateStart > CHANGE_STATE_TIME && isChangeState == 1)
	{
		_changeStateStart = 0;
		isChangeState = 0;
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
	else if (isChangeState == 0)
	{
		if (isUp)
		{
			mario.vy = -MARIO_IN_PIPE_VELOCITY_Y;
			//DebugOut(L"merio y: %f ---- ps: %f \n", mario.y, (position_out_y - MARIO_RACOON_BBOX_HEIGHT));
			//set lại vị trí cũ sau khi mario đã chui ra khỏi ống
			if (mario.y < position_out_y - MARIO_RACOON_BBOX_HEIGHT+13)
			{
				Reset();
				StartChangeState();
			} //kiểm tra vị trí để chuyển cam ra khỏi hidden scene
			else if (inPipe == 1 && mario.y < position_toggle_cam_y)
			{
				inPipe = 0;
				CCamera::GetInstance()->GoBackToNormal();
				mario.SetPosition(POSITION_PLAYER_OUT_PIPE_X, POSITION_PLAYER_OUT_PIPE_Y);
			}
		}
		else {
			if (inPipe == 1 && mario.y > position_toggle_cam_y)
			{
				inPipe = 0;
				CCamera::GetInstance()->AdjustPositionToHiddenScene();
				mario.SetPosition(HIDDEN_SCENE_X + 420, HIDDEN_SCENE_Y + 5);
			}
			mario.vy = MARIO_IN_PIPE_VELOCITY_Y;
		}
	}
	if (isTouchHiddenPipe) mario.vy = MARIO_IN_PIPE_VELOCITY_Y * 4;
}

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateGetIntoPipe();
	return __instance;
}

void CMarioStateGetIntoPipe::Reset()
{
	isUp = isTouchHiddenPipe = false;
	position_out_x = position_out_y = inPipe = 0;
}