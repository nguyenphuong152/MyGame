#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateIdle.h"
#include "Mario.h"

CMarioStateWalk* CMarioStateWalk::__instance = NULL;

CMarioStateWalk::CMarioStateWalk() {
	DebugOut(L"[STATE] create walk \n");
}

void CMarioStateWalk::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::WALK);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_WALKING);
	}
	else if(mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACOON_WALKING);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_WALKING);
	}
}
void CMarioStateWalk::HandleInput(CMario& mario)
{
	CMarioOnGroundStates::HandleInput(mario);
}

void CMarioStateWalk::Update(DWORD dt, CMario& mario)
{
	if (mario.vx > 0) {
		mario.vx += -MARIO_ACCELERATION * dt;
		if (mario.vx < 0) {
			mario.ChangeState(CMarioState::idle.GetInstance());
		}
	}
	else if (mario.vx < 0) {
		mario.vx += MARIO_ACCELERATION * dt;
		if (mario.vx > 0) {
			mario.ChangeState(CMarioState::idle.GetInstance());
		}
	}

	if (mario.vx == 0)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
   
}

CMarioStateWalk* CMarioStateWalk::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateWalk();
	return __instance;
}
