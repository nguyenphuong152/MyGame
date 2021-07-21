#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateIdle.h"
#include "MarioStateStop.h"
#include "MarioStateSit.h"
#include "MarioStateRun.h"
#include "MarioStateDrop.h"
#include "Mario.h"

CMarioStateWalk* CMarioStateWalk::__instance = NULL;

CMarioStateWalk::CMarioStateWalk() {
	DebugOut(L"[STATE] create walk \n");
}

void CMarioStateWalk::Enter(CMario& mario)
{
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_WALK);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON || marioLevel == MARIO_LEVEL_IMMORTAL) {
		mario.SetAnimation(MARIO_ANI_RACCOON_WALK);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_WALK);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_WALK);
	}
}
void CMarioStateWalk::HandleInput(CMario& mario, Input input)
{
	if (input == Input::PRESS_S)
	{

		CMarioOnGroundStates::SetStateJumping(mario);
	}
	else {
		CMarioOnGroundStates::HandleInput(mario, input);
	}
}

void CMarioStateWalk::Update(DWORD dt, CMario& mario)
{
	CalculateAcceleration(MARIO_ACCELERATION, dt, mario);
	
	if (mario.vx == 0)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
	else if (mario.vy > MARIO_AVERAGE_VY_ON_GROUND)
	{
		mario.isOnGround = false;
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
}

void CMarioStateWalk::CalculateAcceleration(float accelerate, DWORD dt, CMario& mario)
{
	if (mario.vx > 0) {
		mario.vx += -accelerate * dt;
		if (mario.vx < 0) {
			if (mario.isSitting)
			{
				mario.ChangeState(CMarioState::sit.GetInstance());
			}
			else
			{
				mario.ChangeState(CMarioState::idle.GetInstance());
			}
		}
	}
	else if (mario.vx < 0) {
		mario.vx += accelerate * dt;
		if (mario.vx > 0) {
			if (mario.isSitting)
			{
				mario.ChangeState(CMarioState::sit.GetInstance());
			}
			else
			{
				mario.ChangeState(CMarioState::idle.GetInstance());
			}
		}
	}
}

CMarioStateWalk* CMarioStateWalk::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateWalk();
	return __instance;
}
