#include "Mario.h"
#include "MarioStateSpin.h"
#include "MarioStateIdle.h"

CMarioStateSpin* CMarioStateSpin::__instance = NULL;

CMarioStateSpin::CMarioStateSpin() {
	DebugOut(L"[STATE] create spin \n");
}

void CMarioStateSpin::Enter(CMario& mario)
{
	mario.SetAnimation(MARIO_ANI_RACCOON_SPIN);
}
void CMarioStateSpin::HandleInput(CMario& mario, Input input)
{
	CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateSpin::Update(DWORD dt, CMario& mario)
{
	mario.vx = 0.005f * mario.nx;
	if (GetTickCount64()-_spinningStart > MARIO_SPINNING_TIME)
	{
		mario.vx = 0;
		isAttack = false;
		mario.ChangeState(CMarioState::idle.GetInstance());
		
	}
}


CMarioStateSpin* CMarioStateSpin::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSpin();
	return __instance;
}
