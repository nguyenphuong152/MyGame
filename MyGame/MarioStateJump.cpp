#include "Mario.h"
#include "MarioStateJump.h"
#include "MarioStateDrop.h"


CMarioStateJump* CMarioStateJump::__instance = NULL;

CMarioStateJump::CMarioStateJump() {
	DebugOut(L"[STATE] create jump \n");

}

void CMarioStateJump::Enter(CMario& mario)
{
	mario.isOnGround = false;
	mario.canFlyHigh = false;
	SetCurrentState(MarioStates::JUMP);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_JUMP);
	}
	else if(mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_JUMP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_JUMP);
	}
}
void CMarioStateJump::HandleInput(CMario& mario,Input input)
{
	CMarioOnAirStates::HandleInput(mario,  input);
}

void CMarioStateJump::Update(DWORD dt, CMario& mario)
{
	if (mario.vy > 0)
	{
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
}

CMarioStateJump* CMarioStateJump::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateJump();
	return __instance;
}
