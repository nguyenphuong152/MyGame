#include "MarioStateKick.h"
#include "MarioStateIdle.h"
#include "Mario.h"

CMarioStateKick* CMarioStateKick::__instance = NULL;

CMarioStateKick::CMarioStateKick() {
	DebugOut(L"[STATE] create kick \n");
}

void CMarioStateKick::Enter(CMario& mario)
{
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_KICK);
	}
	else if (mario.level == MARIO_LEVEL_RACOON || mario.level == MARIO_LEVEL_IMMORTAL) {
		mario.SetAnimation(MARIO_ANI_RACCOON_KICK);
	}
	else if (mario.level == MARIO_LEVEL_FIRE)
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
		mario.ChangeState(CMarioState::idle.GetInstance());
		mario.isKicking = false;
	}
	if (mario.isKicking)
	{
		mario.canHoldShell = false;
	}
}


CMarioStateKick* CMarioStateKick::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateKick();
	return __instance;
}
