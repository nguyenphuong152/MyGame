﻿#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateIdle.h"
#include "MarioStateStop.h"
#include "MarioStateSit.h"
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
void CMarioStateWalk::HandleInput(CMario& mario,Input input)
{
	CMarioOnGroundStates::HandleInput(mario, input);
}

void CMarioStateWalk::Update(DWORD dt, CMario& mario)
{
	CalculateAcceleration(MARIO_ACCELERATION, dt, mario);
	if (mario.vx == 0)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
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
