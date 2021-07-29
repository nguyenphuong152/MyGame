#include "Mario.h"
#include "MarioStateFly.h"
#include "MarioStateDrop.h"
#include "MarioStateIdle.h"


CMarioStateFly* CMarioStateFly::__instance = NULL;

CMarioStateFly::CMarioStateFly() {
	DebugOut(L"[STATE] create fly \n");

}

void CMarioStateFly::Enter(CMario& mario)
{
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_FLY);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_FLY);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_FLY);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_FLY);
	}
}
void CMarioStateFly::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	if (input == Input::PRESS_S&&mario.GetLevel()==MARIO_LEVEL_RACOON)
	{
		mario.isOnGround = false;
		mario.vy = -MARIO_FLYING_SPEED;
		mario.vx = mario.nx * MARIO_WALKING_SPEED;
	}
	else {
		CMarioOnAirStates::HandleInput(mario, input);
	}
}

void CMarioStateFly::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround)
	{
		if (mario.isAutoWalk)
			mario.AutoWalk();
		else 
		   mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateFly* CMarioStateFly::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateFly();
	return __instance;
}
