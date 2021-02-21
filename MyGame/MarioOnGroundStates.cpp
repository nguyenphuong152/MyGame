#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"
#include "MarioStateRun.h"
#include "MarioStatePreFly.h"
#include "MarioStateFly.h"
#include "MarioStateSpin.h"

CMarioOnGroundStates::CMarioOnGroundStates()
{
}

void CMarioOnGroundStates::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();

	if (input == Input::KEYSTATE)
	{
		if (game->IsKeyDown(DIK_LEFT)) {
			if (mario.powerMode && mario.vx != 0)
			{	
				//cong power cho mario khi mario o powermode, moi giay tang 1 power
				if (GetTickCount() - mario.power_start > 0 && mario.power < 72) {
					mario.power++;
				}
				if (mario.power == 72)
				{
					//DebugOut(L"[after] run time %d \n", mario.power);
					mario.SetVelocityX(mario.nx * MARIO_PRE_FLYING_SPEED);
					mario.ChangeState(CMarioState::pre_fly.GetInstance());
				}
				else{
					mario.SetVelocityX(mario.nx * MARIO_RUNNING_SPEED);
					mario.ChangeState(CMarioState::run.GetInstance());
				}
			}
			else if (mario.vx > 0)
			{
				mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
				mario.ChangeState(CMarioState::stop.GetInstance());
			}
			else
			{
				SetStateWalking(DIRECTION_RIGHT_TO_LEFT, mario);
			}
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{
			if (mario.powerMode & mario.vx != 0)
			{
				if (GetTickCount() - mario.power_start > 0&&mario.power<72) mario.power++;
				if (mario.power == 72)
				{
					mario.SetVelocityX(mario.nx * MARIO_PRE_FLYING_SPEED);
					mario.ChangeState(CMarioState::pre_fly.GetInstance());
				}
				else {
					mario.SetVelocityX(mario.nx * MARIO_RUNNING_SPEED);
					mario.ChangeState(CMarioState::run.GetInstance());
				}
			}
			else if (mario.vx < 0)
			{
				mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
				mario.ChangeState(CMarioState::stop.GetInstance());

			}
			else {
				SetStateWalking(DIRECTION_LEFT_TO_RIGHT, mario);
			}
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			if (mario.isOnGround && mario.level != MARIO_LEVEL_SMALL)
			{
				mario.ChangeState(CMarioState::sit.GetInstance());
			}
		}
		//thieeu nhay cao va  nhay thap
	}

	if (input == Input::PRESS_S)
	{
		SetStateJumping(MARIO_JUMP_SPEED_Y, mario);
	}
	else if (input == Input::PRESS_DOWN && mario.vx == 0)
	{
		if (mario.isOnGround && mario.level != MARIO_LEVEL_SMALL)
		{
			mario.ChangeState(CMarioState::sit.GetInstance());
		}
	}
	else if (input == Input::PRESS_A)
	{
		if (mario.level == MARIO_LEVEL_RACOON)
		{
			mario.ChangeState(CMarioState::spin.GetInstance());
		}
	}
}



void CMarioOnGroundStates::SetStateWalking(int direction, CMario& mario)
{
	mario.SetDirection(direction);
	mario.SetVelocityX(direction * MARIO_WALKING_SPEED);
	mario.ChangeState(CMarioState::walk.GetInstance());
}

void CMarioOnGroundStates::SetStateJumping(float jumpSpeed, CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.isOnGround = false;
		mario.SetVelocityY(-jumpSpeed);
		mario.ChangeState(CMarioState::jump.GetInstance());
	}
}