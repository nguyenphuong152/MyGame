#include "MarioStateRun.h"
#include "MarioStateJump.h"
#include "MarioStateIdle.h"
#include "MarioStateStop.h"
#include "MarioStatePreFly.h"
#include "MarioStateWalk.h"
#include "Mario.h"

CMarioStateRun* CMarioStateRun::__instance = NULL;

CMarioStateRun::CMarioStateRun() {
	DebugOut(L"[STATE] create run \n");
}

void CMarioStateRun::Enter(CMario& mario)
{
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_RUN);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON || marioLevel == MARIO_LEVEL_IMMORTAL) {
		mario.SetAnimation(MARIO_ANI_RACCOON_RUN);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_RUN);
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
	if (mario.isAutoWalk == false)
	{
		if (!mario.powerMode)
		{
			mario.ChangeState(CMarioState::walk.GetInstance());
		}
		else {
			mario.powerLevel += 10;
		}
	}
}


CMarioStateRun* CMarioStateRun::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateRun();
	return __instance;
}
