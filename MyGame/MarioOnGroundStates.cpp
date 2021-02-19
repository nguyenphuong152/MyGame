#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"

CMarioOnGroundStates::CMarioOnGroundStates()
{
}

void CMarioOnGroundStates::HandleInput(CMario& mario,Input input)
{
	CGame* game = CGame::GetInstance();
	if (input == Input::KEYSTATE)
	{
		if (game->IsKeyDown(DIK_LEFT)) {
			if (mario.vx > 0)
			{
				mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
				mario.ChangeState(CMarioState::stop.GetInstance());
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
				mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
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
		else if (game->IsKeyDown(DIK_S))
		{
			if (mario.isOnGround&&mario.canFlyHigh)
			{
				mario.canFlyHigh = false;
				mario.SetVelocityY(-MARIO_JUMP_HIGH_SPEED_Y);
				mario.ChangeState(CMarioState::jump.GetInstance());
			}
		}
	}
	
	if (input == Input::PRESS_S)
	{
		SetStateJumping(MARIO_JUMP_SPEED_Y,mario);
	}
	else if (input == Input::PRESS_DOWN && mario.vx==0)
	{
		if (mario.isOnGround && mario.level!=MARIO_LEVEL_SMALL)
		{
			mario.ChangeState(CMarioState::sit.GetInstance());
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