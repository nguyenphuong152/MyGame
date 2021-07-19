#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"
#include "MarioStateRun.h"
#include "MarioStatePreFly.h"
#include "MarioStateFly.h"
#include "MarioStateGetIntoPipe.h"
#include "MarioStateSpin.h"
#include "MarioStateThrowingFireball.h"
#include "FireBall.h"
#include "FireBallPool.h"

CMarioOnGroundStates::CMarioOnGroundStates()
{
}

void CMarioOnGroundStates::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();

	if (input == Input::KEYSTATE)
	{
		if (game->IsKeyDown(DIK_LEFT)) {
			if (mario.vx > 0)
			{
				mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
				mario.ChangeState(CMarioState::stop.GetInstance());
			}
			else if (mario.powerMode)
			{
				if (mario.powerLevel == MARIO_POWER_LEVEL)
				{
					mario.ChangeState(CMarioState::pre_fly.GetInstance());
				}
				else {
					SetStateRunning(DIRECTION_RIGHT_TO_LEFT, mario);
				}
			}
			else 
			{
				SetStateWalking(DIRECTION_RIGHT_TO_LEFT, mario);
			}
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{
			if (mario.vx < 0)
			{
				mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
				mario.ChangeState(CMarioState::stop.GetInstance());

			}
			else if (mario.powerMode)
			{
				if (mario.powerLevel == MARIO_POWER_LEVEL)
				{
					mario.ChangeState(CMarioState::pre_fly.GetInstance());
				}
				else {
					SetStateRunning(DIRECTION_LEFT_TO_RIGHT, mario);
				}
			}
			else {
				SetStateWalking(DIRECTION_LEFT_TO_RIGHT, mario);
			}
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (mario.isOnGround && mario.GetLevel() != MARIO_LEVEL_SMALL)
			{
				if (mario.canGoIntoPipe)
				{
					mario.ChangeState(CMarioState::go_to_pipe.GetInstance());
					CMarioState::go_to_pipe.GetInstance()->inPipe = 1;
				}
				else {
					mario.ChangeState(CMarioState::sit.GetInstance());
					CMarioState::sit.GetInstance()->SetPositionBeforeSitting(mario);
				}
			}
		}
	}

	if (input == Input::PRESS_S)
	{
		SetStateJumping( mario);
	}
	else if (input == Input::PRESS_DOWN && mario.vx == 0)
	{
		if (mario.isOnGround && mario.GetLevel() != MARIO_LEVEL_SMALL)
		{
			mario.ChangeState(CMarioState::sit.GetInstance());
		}
	}
	else if (input == Input::PRESS_A)
	{
		mario.powerMode = true;
		if (mario.GetLevel() == MARIO_LEVEL_RACOON)
		{
			CMarioState::spin.GetInstance()->isAttack = true;
			mario.ChangeState(CMarioState::spin.GetInstance());
			CMarioState::spin.GetInstance()->StartSpinning();
		}
		else if (mario.GetLevel() == MARIO_LEVEL_FIRE)
		{
			CFireball* fireball = CFireBallPool::GetInstance()->Create();
			if (fireball != NULL)
			{
				mario.ChangeState(CMarioState::throw_fireball.GetInstance());
				fireball->AllocateFireballToMario();
				CMarioState::throw_fireball.GetInstance()->StartThrowing();
			}
		}
	}
    else if (input == Input::RELEASE_A)
	{
		CMarioState::spin.GetInstance()->isAttack = false;
	}
}



void CMarioOnGroundStates::SetStateWalking(int direction, CMario& mario)
{
	mario.SetDirection(direction);
	mario.SetVelocityX(direction * MARIO_WALKING_SPEED);
	if (mario.isStuckWithMiniGoomba)
	{
		mario.SetVelocityX(direction * MARIO_WALKING_SPEED/2);
	}
	mario.ChangeState(CMarioState::walk.GetInstance());
}

void CMarioOnGroundStates::SetStateRunning(int direction, CMario& mario)
{
	if (mario.isStuckWithMiniGoomba == false)
	{
		mario.SetDirection(direction);
		mario.SetVelocityX(direction * MARIO_RUNNING_SPEED);
		mario.ChangeState(CMarioState::run.GetInstance());
	}
}

void CMarioOnGroundStates::SetStateJumping(CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.canJumpHigh = true;
		mario.ChangeState(CMarioState::jump.GetInstance());
		CMarioState::jump.GetInstance()->StartJumping();
	}
}