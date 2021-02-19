#include "Mario.h"
#include "MarioStateStop.h"
#include "MarioStateIdle.h"

CMarioStateStop* CMarioStateStop::__instance = NULL;

CMarioStateStop::CMarioStateStop() {
	DebugOut(L"[STATE] create stop \n");
}

void CMarioStateStop::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::STOP);
	if (mario.level == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_BIG_STOP);
	}
	else if (mario.level == MARIO_LEVEL_RACOON)
	{
		mario.SetAnimation(MARIO_ANI_RACOON_STOP);
	}
	else
	{
		mario.SetAnimation(MARIO_ANI_SMALL_STOP);
	}
}
void CMarioStateStop::HandleInput(CMario& mario)
{
	//
	CMarioOnGroundStates::HandleInput(mario);
}

void CMarioStateStop::Update(DWORD dt, CMario& mario)
{
	CalculateSkidAcceleration(MARIO_ACCELERATION, dt, mario);
	if (mario.vx == 0)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

void CMarioStateStop::CalculateSkidAcceleration(float accelerate, DWORD dt, CMario& mario)
{
	if (mario.vx > 0) {
		mario.vx += -accelerate * dt;
		if (mario.vx < 0) {
			mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
			mario.ChangeState(CMarioState::idle.GetInstance());
		}
	}
	else if (mario.vx < 0) {
		mario.vx += accelerate * dt;
		if (mario.vx > 0) {
			mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
			mario.ChangeState(CMarioState::idle.GetInstance());
		}
	}

}

CMarioStateStop* CMarioStateStop::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateStop();
	return __instance;
}
