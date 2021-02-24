#include "Mario.h"
#include "MarioStateSit.h"
#include "MarioStateIdle.h"
#include "MarioStateWalk.h"


CMarioStateSit* CMarioStateSit::__instance = NULL;

CMarioStateSit::CMarioStateSit() {
	DebugOut(L"[STATE] create sit \n");

}

void CMarioStateSit::Enter(CMario& mario)
{
	mario.isSitting = true;
	mario.SetVelocityX(0);
	SetCurrentState(MarioStates::SIT);
	if (mario.level == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_BIG_SIT);
	}
	else if (mario.level == MARIO_LEVEL_RACOON)
	{
		mario.SetAnimation(MARIO_ANI_RACCOON_SIT);
	}
}
void CMarioStateSit::HandleInput(CMario& mario,Input input)
{
	CGame* game = CGame::GetInstance();

	if (input == Input::RELEASE_DOWN)
	{
		SetPositionAferSitting(mario);
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
	else  if (input == Input::PRESS_S)
	{
		if (mario.isOnGround)
		{
			mario.StartHighJump();
			mario.SetVelocityY(-SIT_JUMP_VELOCITY_Y);
			mario.isOnGround = false;
		}
	}
	else if (input == Input::RELEASE_S)
	{
		mario.canFlyHigh = false;
		mario.highjump_start = 0;
	}
	//thieu ngoi nhan s nhay cao nhay thap

	if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
	{
		SetPositionAferSitting(mario);
		mario.ChangeState(CMarioState::walk.GetInstance());
	}
	else if (game->IsKeyDown(DIK_S) && mario.canFlyHigh &&mario.vy<0)
	{
		mario.SetVelocityY(-0.2);
		if (GetTickCount() - mario.highjump_start > TIME_TURN_OFF_HIGH_JUMP)
		{
			mario.canFlyHigh = false;
			mario.highjump_start = 0;
			mario.SetVelocityY(SIT_DROP_VELOCITY_Y);
		}
	}
}

void CMarioStateSit::Update(DWORD dt, CMario& mario)
{
	if ((GetTickCount() - mario.highjump_start > TIME_TOGGLE_HIGH_JUMP_WHEN_SITTING) && !mario.isOnGround&&!mario.canFlyHigh)
	{
		mario.canFlyHigh = true;
	}
}

void CMarioStateSit::SetPositionAferSitting(CMario& mario)
{
	mario.isSitting = false;

	if (mario.level == MARIO_LEVEL_BIG)
	{
		mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
	else
	{
		mario.y -= MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
}

CMarioStateSit* CMarioStateSit::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSit();
	return __instance;
}
