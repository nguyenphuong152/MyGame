#include "Mario.h"
#include "MarioStateThrowingFireball.h"
#include "MarioStateIdle.h"

CMarioStateThrowFireball* CMarioStateThrowFireball::__instance = NULL;

CMarioStateThrowFireball::CMarioStateThrowFireball() {
	_throwingStart = 0;
	DebugOut(L"[STATE] create throw fireball \n");
}

void CMarioStateThrowFireball::Enter(CMario& mario)
{
	mario.SetAnimation(MARIO_ANI_FIRE_SHOOT_FIREBALL_IDLE);
}
void CMarioStateThrowFireball::HandleInput(CMario& mario, Input input)
{
	CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateThrowFireball::Update(DWORD dt, CMario& mario)
{
	if (GetTickCount64() - _throwingStart > MARIO_THROWING_TIME)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}


CMarioStateThrowFireball* CMarioStateThrowFireball::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateThrowFireball();
	return __instance;
}
