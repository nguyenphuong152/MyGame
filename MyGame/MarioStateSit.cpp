#include "Mario.h"
#include "MarioStateSit.h"
#include "MarioStateIdle.h"
#include "MarioStateWalk.h"


CMarioStateSit* CMarioStateSit::__instance = NULL;

CMarioStateSit::CMarioStateSit() {
	DebugOut(L"[STATE] create sit \n");
	preparing = 0;
	_jumpingStart = 0;
	_prepareWalkBehindMapStart = 0;
}

void CMarioStateSit::Enter(CMario& mario)
{
	mario.isSitting = true;
	mario.vx = 0;
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_BIG_SIT);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON || marioLevel == MARIO_LEVEL_IMMORTAL)
	{
		mario.SetAnimation(MARIO_ANI_RACCOON_SIT);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_SIT);
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
			mario.vy = -SIT_JUMP_Y;
			StartJumping();
			mario.canJumpHigh = true;
			mario.isOnGround = false;
		}
	}
	else if (input == Input::RELEASE_S)
	{
		mario.canJumpHigh = false;
	}

	if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
	{
		SetPositionAferSitting(mario);
		mario.ChangeState(CMarioState::walk.GetInstance());
	}
}

void CMarioStateSit::Update(DWORD dt, CMario& mario)
{
	if (mario.canJumpHigh)
	{
		if (GetTickCount64() - _jumpingStart > MARIO_JUMP_TIME)
		{
			mario.canJumpHigh = false;
		}
		else {
			mario.vy = -MARIO_JUMP_SPEED_Y;
		}
	}

	if (mario.isOnSpecialBox && preparing == 0) StartPrepair();
	if (preparing == 1 && GetTickCount64() - _prepareWalkBehindMapStart > SITTING_TIME)
	{
		ResetPrepair();
		mario.isOnSpecialBox = false;
		mario.canWalkBehindMap = true;
		mario.WalkBehindStart();
	}
}

void CMarioStateSit::SetPositionAferSitting(CMario& mario)
{
	mario.isSitting = false;
	if (mario.GetLevel() == MARIO_LEVEL_BIG||mario.GetLevel()==MARIO_LEVEL_FIRE)
	{
		mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACOON)
	{
		mario.y -= MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
}

CMarioStateSit* CMarioStateSit::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSit();
	return __instance;
}

void CMarioStateSit::SetPositionBeforeSitting(CMario &mario)
{
	if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
	{
		mario.y += MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACOON)
	{
		mario.y += MARIO_RACOON_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
	}
}