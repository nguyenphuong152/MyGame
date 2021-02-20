#include "Mario.h"
#include "MarioStateFly.h"
#include "MarioStateIdle.h"


CMarioStateFly* CMarioStateFly::__instance = NULL;

CMarioStateFly::CMarioStateFly() {
	DebugOut(L"[STATE] create fly \n");

}

void CMarioStateFly::Enter(CMario& mario)
{
	mario.isOnGround = false;

	SetCurrentState(MarioStates::FLY);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_FLY);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACOON_FLY);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_FLY);
	}
}
void CMarioStateFly::HandleInput(CMario& mario, Input input)
{
	
}

void CMarioStateFly::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateFly* CMarioStateFly::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateFly();
	return __instance;
}
