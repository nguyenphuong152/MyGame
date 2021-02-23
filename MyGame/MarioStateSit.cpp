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
		mario.StartHighJump();
		if (mario.isOnGround)
		{
			mario.isOnGround = false;
			mario.SetVelocityY(-0.3);
		}
	}

	if (input == Input::RELEASE_S)
	{
		mario.canFlyHigh = false;
	}

	if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
	{
		SetPositionAferSitting(mario);
		mario.ChangeState(CMarioState::walk.GetInstance());
	}
}

void CMarioStateSit::Update(DWORD dt, CMario& mario)
{
	if (mario.isSitting)
	{
		if ((GetTickCount() - mario.highjump_start > 50) && !mario.canFlyHigh)
		{
			mario.canFlyHigh = true;
		}
		if (mario.canFlyHigh)
		{
			mario.SetVelocityY(-0.3);
		}

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
