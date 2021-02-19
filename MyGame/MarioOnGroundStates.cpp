#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"

CMarioOnGroundStates::CMarioOnGroundStates()
{
	DebugOut(L"[STATE] create on ground state \n");
}

void CMarioOnGroundStates::HandleInput(CMario& mario)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_LEFT)) {
		if (mario.vx > 0 )
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
		if (mario.vx <0)
		{
			mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
			mario.ChangeState(CMarioState::stop.GetInstance());
			
		}
		else {

			SetStateWalking(DIRECTION_LEFT_TO_RIGHT, mario);
		}
	}
	else if (game->IsKeyDown(DIK_S))
	{
		if (mario.isOnGround)
		{
			mario.isOnGround = false;
			mario.SetVelocityY(-MARIO_JUMP_SPEED_Y);
			mario.ChangeState(CMarioState::jump.GetInstance());
		}
	}
	else if (game->IsKeyDown(DIK_DOWN))
	{
		if (mario.level != MARIO_LEVEL_SMALL && mario.isOnGround)
		{
			mario.SetVelocityX(0);
			mario.ChangeState(CMarioState::sit.GetInstance());
		}
	}

	//DebugOut(L"[after all ]mario after nx: %d \n", mario.nx);
	DebugOut(L"[after all]state: %d \n", GetCurrentState());
	DebugOut(L"[after all]ani: %d \n", mario.GetCurrentAnimation());
}

void CMarioOnGroundStates::SetStateWalking(int direction, CMario& mario)
{
	mario.SetDirection(direction);
	mario.SetVelocityX(direction * MARIO_WALKING_SPEED);
	mario.ChangeState(CMarioState::walk.GetInstance());
}