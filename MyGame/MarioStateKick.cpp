#include "MarioStateKick.h"
#include "MarioStateIdle.h"
#include "Mario.h"

CMarioStateKick* CMarioStateKick::__instance = NULL;

CMarioStateKick::CMarioStateKick() {
	DebugOut(L"[STATE] create kick \n");
}

void CMarioStateKick::Enter(CMario& mario)
{
	mario.SetVelocityX(0);
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_KICK);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON || marioLevel == MARIO_LEVEL_IMMORTAL) {
		mario.SetAnimation(MARIO_ANI_RACCOON_KICK);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_KICK);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_KICK);
	}
}
void CMarioStateKick::HandleInput(CMario& mario, Input input)
{
	CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateKick::Update(DWORD dt, CMario& mario)
{
	if (GetTickCount64()-_kickingStart > MARIO_KICKING_TIME)
	{
		_kickingStart = 0;
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}


CMarioStateKick* CMarioStateKick::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateKick();
	return __instance;
}
