#include "MarioStateGetIntoPipe.h"
#include "MarioStateIdle.h"
#include "MarioStateJump.h"
#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "Camera.h"

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::__instance = NULL;



void CMarioStateGetIntoPipe::HandleSecretScreen1_1(CMario& mario)
{
	if (isInPipe == 1 && GetTickCount64() - inPipeStart > IN_PIPE_TIME/2)
	{
		ResetInPipe();

		CHiddenScene* h = CGame::GetInstance()->GetMainCamera()->GetHiddenScene();
		if (dir == DOWN)
		{
			mario.SetPosition((float)(h->player_pos_in_x),(float)( h->player_pos_in_y));
			CGame::GetInstance()->GetMainCamera()->AdjustPositionToHiddenScene();
			isTouchHiddenPipe = true;
		}
		else
		{
			dir = DOWN;
			StartChangeState();
		}
	}

	if (isOutPipe == 1 && GetTickCount64() - outPipeStart > IN_PIPE_SHORT_TIME)
	{
		CCamera* cam = CGame::GetInstance()->GetMainCamera();
		CHiddenScene* h = cam->GetHiddenScene();

		ResetOutPipe();
		mario.SetPosition((float)(h->player_pos_out_pipe_x),(float)( h->player_pos_out_pipe_y));
		cam->GoBackToNormal();
		StartInPipe();
	}
}

void CMarioStateGetIntoPipe::HandleSecretScreen1_3(CMario& mario)
{
	if (isInPipe == 1 && GetTickCount64() - inPipeStart > IN_PIPE_TIME/2)
	{
		ResetInPipe();
		mario.GoBackToNormalScene();
		CGame::GetInstance()->GetMainCamera()->GoBackToNormal();
	}
}

CMarioStateGetIntoPipe::CMarioStateGetIntoPipe() {
	inPipeStart = 0;
	DebugOut(L"[STATE] create go to pipe \n");
}

void CMarioStateGetIntoPipe::Enter(CMario& mario)
{
	if (isTouchHiddenPipe) mario.SetAnimation(MARIO_ANI_DROP_FROP_PIPE);
	else mario.SetAnimation(MARIO_ANI_GET_INTO_PIPE);
}

void CMarioStateGetIntoPipe::HandleInput(CMario& mario, Input input)
{

}

void CMarioStateGetIntoPipe::Update(DWORD dt, CMario& mario)
{
	mario.vx = 0;
	mario.vy = MARIO_IN_PIPE_VELOCITY_Y * dir;

	if (CGame::GetInstance()->current_scene == WORLD1_1_MAP)
		HandleSecretScreen1_1(mario);
	else if (CGame::GetInstance()->current_scene == WORLD1_3_MAP)
		HandleSecretScreen1_3(mario);

	if (isChangeState == 1 && GetTickCount64() - _changeStateStart > CHANGE_STATE_TIME)
	{
		ResetChangeState();
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateGetIntoPipe();
	return __instance;
}

void CMarioStateGetIntoPipe::GetBoundingBox(CMario& mario,float& l, float& t, float& r, float& b)
{
	CMarioState::GetBoundingBox(mario, l, t, r, b);
	r = l + MARIO_GO_TO_PIPE_BBOX_WIDTH;
	b = t + MARIO_BIG_BBOX_HEIGHT+5;
}



