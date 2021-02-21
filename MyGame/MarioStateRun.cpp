#include "MarioStateRun.h"
#include "MarioStateJump.h"
#include "MarioStateIdle.h"
#include "MarioStateStop.h"
#include "MarioStatePreFly.h"
#include "Mario.h"

CMarioStateRun* CMarioStateRun::__instance = NULL;

CMarioStateRun::CMarioStateRun() {
	DebugOut(L"[STATE] create run \n");
}

void CMarioStateRun::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::RUN);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_RUN);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACOON_RUN);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_RUN);
	}
}
void CMarioStateRun::HandleInput(CMario& mario, Input input)
{
    CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateRun::Update(DWORD dt, CMario& mario)
{
}


CMarioStateRun* CMarioStateRun::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateRun();
	return __instance;
}
