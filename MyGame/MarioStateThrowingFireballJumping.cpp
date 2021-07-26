#include "Mario.h"
#include "MarioStateThrowingFireballJumping.h"
#include "MarioStateDrop.h"

CMarioStateThrowFireballJumping* CMarioStateThrowFireballJumping::__instance = NULL;

CMarioStateThrowFireballJumping::CMarioStateThrowFireballJumping() {
	_throwingStart = 0;
	DebugOut(L"[STATE] create throw fireball jumping \n");
}

void CMarioStateThrowFireballJumping::Enter(CMario& mario)
{
	mario.SetAnimation(MARIO_ANI_FIRE_SHOOT_FIREBALL_JUMP);
}
void CMarioStateThrowFireballJumping::HandleInput(CMario& mario, Input input)
{
	CMarioStateJump::HandleInput(mario, input);
}

void CMarioStateThrowFireballJumping::Update(DWORD dt, CMario& mario)
{
	if (GetTickCount64() - _throwingStart > MARIO_THROWING_TIME)
	{
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
}


CMarioStateThrowFireballJumping* CMarioStateThrowFireballJumping::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateThrowFireballJumping();
	return __instance;
}
