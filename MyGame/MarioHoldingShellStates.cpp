﻿#include "MarioHoldingShellStates.h"
#include "MarioStateHoldShellAndRun.h"
#include "MarioStateHoldShellAndJump.h"
#include "Mario.h"
#include "MarioStateKick.h"

CMarioHoldingShellStates::CMarioHoldingShellStates()
{
}

void CMarioHoldingShellStates::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_LEFT))
	{
		//thiếu xoay qua phảo thắng lại miếng r chạy tiếp
		mario.nx = DIRECTION_RIGHT_TO_LEFT;
		mario.vx = mario.nx*MARIO_RUNNING_SPEED;
		mario.ChangeState(CMarioState::holdshell_run.GetInstance());
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		mario.nx = DIRECTION_LEFT_TO_RIGHT;
		mario.vx = mario.nx * MARIO_RUNNING_SPEED;
		mario.ChangeState(CMarioState::holdshell_run.GetInstance());
	}

	if (input == Input::RELEASE_A)
	{
		mario.powerMode = false;
		mario.ChangeState(CMarioState::kick.GetInstance());
		CMarioState::kick.GetInstance()->StartKicking();
	}else if (input == Input::PRESS_S)
	{
		if (mario.isOnGround)
		{
			mario.canJumpHigh = true;
			mario.ChangeState(CMarioState::holdshell_jump.GetInstance());
			CMarioState::holdshell_jump.GetInstance()->StartJumping();
		}
	}
}




