#include "Mario.h"
#include "MarioStateSpin.h"
#include "MarioStateIdle.h"

CMarioStateSpin* CMarioStateSpin::__instance = NULL;

CMarioStateSpin::CMarioStateSpin() {
	DebugOut(L"[STATE] create spin \n");

}

void CMarioStateSpin::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::SIT);
	mario.SetAnimation(MARIO_ANI_RACOON_SPIN);
}
void CMarioStateSpin::HandleInput(CMario& mario, Input input)
{
	if (input == Input::RELEASE_A)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
	//CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateSpin::Update(DWORD dt, CMario& mario)
{
}


CMarioStateSpin* CMarioStateSpin::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSpin();
	return __instance;
}
