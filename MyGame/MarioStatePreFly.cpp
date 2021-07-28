#include "MarioStatePreFly.h"
#include "MarioStateFly.h"
#include "MarioStateRun.h"
#include "Mario.h"

CMarioStatePreFly* CMarioStatePreFly::__instance = NULL;

CMarioStatePreFly::CMarioStatePreFly() {
	DebugOut(L"[STATE] create pre-fly \n");
}

void CMarioStatePreFly::Enter(CMario& mario)
{
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_PRE_FLY);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON || marioLevel == MARIO_LEVEL_IMMORTAL) {
		mario.SetAnimation(MARIO_ANI_RACCOON_PRE_FLY);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_PRE_FLY);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_PRE_FLY);
	}
}
void CMarioStatePreFly::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	if (input == Input::PRESS_S)
	{
		mario.isOnGround = false;
		mario.vy = -MARIO_START_FLYING_SPEED;
		mario.ChangeState(CMarioState::fly.GetInstance());
	}
}

void CMarioStatePreFly::Update(DWORD dt, CMario& mario)
{
	if (!mario.powerMode || CMarioState::run.GetInstance()->decreasePower)
	{
		mario.ChangeState(CMarioState::run.GetInstance());
	}
}


CMarioStatePreFly* CMarioStatePreFly::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStatePreFly();
	return __instance;
}
