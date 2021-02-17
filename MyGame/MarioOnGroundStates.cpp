#include "MarioOnGroundStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"

CMarioOnGroundStates::CMarioOnGroundStates()
{
	DebugOut(L"[STATE] create on ground state \n");
}

void CMarioOnGroundStates::HandleInput(CMario& mario)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_LEFT))
	{
		mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
		mario.SetVelocityX(-MARIO_WALKING_SPEED);
		mario.ChangeState(CMarioState::walk.GetInstance());
	}
	if (game->IsKeyDown(DIK_RIGHT))
	{
		mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
		mario.SetVelocityX(MARIO_WALKING_SPEED);
		mario.ChangeState(CMarioState::walk.GetInstance());
	}
	if (game->IsKeyDown(DIK_S))
	{
		if (mario.isOnGround)
		{
			mario.isOnGround = false;
			mario.SetVelocityY(-MARIO_JUMP_SPEED_Y);
			mario.ChangeState(CMarioState::jump.GetInstance());
		}
	}
	if (game->IsKeyDown(DIK_DOWN))
	{
		if (mario.level!=MARIO_LEVEL_SMALL && mario.isOnGround)
		{
			mario.SetVelocityX(0);
			mario.ChangeState(CMarioState::sit.GetInstance());
		}
	}
}