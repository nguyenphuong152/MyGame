#include "Mario.h"
#include "MarioStateFly.h"
#include "MarioStateIdle.h"


CMarioStateFly* CMarioStateFly::__instance = NULL;

CMarioStateFly::CMarioStateFly() {
	DebugOut(L"[STATE] create fly \n");

}

void CMarioStateFly::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::FLY);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_FLY);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_FLY);
	}
	else if (mario.level == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_DROP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_FLY);
	}
}
void CMarioStateFly::HandleInput(CMario& mario, Input input)
{
	if (input == Input::PRESS_S)
	{
		mario.isOnGround = false;
		mario.SetVelocityY(-0.4);
		mario.SetVelocityX(mario.nx * MARIO_WALKING_SPEED);
		//CMarioOnAirStates::HandleInput(mario,input);
	}
}

void CMarioStateFly::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround|| mario.level == MARIO_LEVEL_SMALL)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateFly* CMarioStateFly::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateFly();
	return __instance;
}
