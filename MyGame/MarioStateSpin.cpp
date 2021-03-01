#include "Mario.h"
#include "MarioStateSpin.h"
#include "MarioStateIdle.h"

CMarioStateSpin* CMarioStateSpin::__instance = NULL;

CMarioStateSpin::CMarioStateSpin() {
	DebugOut(L"[STATE] create spin \n");
	_spinningTime = 0;
}

void CMarioStateSpin::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::SPIN);
	mario.SetAnimation(MARIO_ANI_RACCOON_SPIN);
}
void CMarioStateSpin::HandleInput(CMario& mario, Input input)
{
	CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateSpin::Update(DWORD dt, CMario& mario)
{
	_spinningTime++;
	if (_spinningTime > MARIO_SPINNING_TIME)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
		_spinningTime = 0;
	}
}


CMarioStateSpin* CMarioStateSpin::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSpin();
	return __instance;
}
