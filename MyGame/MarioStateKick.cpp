#include "MarioStateKick.h"
#include "MarioStateIdle.h"
#include "Mario.h"

CMarioStateKick* CMarioStateKick::__instance = NULL;

CMarioStateKick::CMarioStateKick() {
	DebugOut(L"[STATE] create kick \n");
}

void CMarioStateKick::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::KICK);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_KICK);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_KICK);
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
	if (!mario.isKicking)
	{
		mario.SetVelocityX(0);
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}


CMarioStateKick* CMarioStateKick::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateKick();
	return __instance;
}
