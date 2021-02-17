#include "MarioStateIdle.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioOnGroundStates.h"
#include "Mario.h"

CMarioStateIdle* CMarioStateIdle::__instance = NULL;

CMarioStateIdle::CMarioStateIdle() {
	DebugOut(L"[STATE] create idle \n");
}

void CMarioStateIdle::Enter(CMario &mario)
{
	SetCurrentState(MarioStates::IDLE);
	mario.SetVelocityX(0);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_IDLE);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_IDLE);
	}
}
void CMarioStateIdle::HandleInput(CMario& mario) 
{
	CMarioOnGroundStates::HandleInput(mario);
}

void CMarioStateIdle::Update(DWORD dt,CMario& mario)
{

}

CMarioStateIdle* CMarioStateIdle::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateIdle();
	return __instance;
}
