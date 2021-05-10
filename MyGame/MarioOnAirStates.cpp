#include "MarioOnAirStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"
#include "MarioStateRun.h"
#include "MarioStatePreFly.h"
#include "FireBall.h"
#include "FireBallPool.h"
#include "MarioStateSpin.h"
#include "MarioStateThrowingFireballJumping.h"

CMarioOnAirStates::CMarioOnAirStates()
{
}

void CMarioOnAirStates::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_LEFT))
	{
		mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
		mario.SetVelocityX(-MARIO_WALKING_SPEED);
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
		mario.SetVelocityX(MARIO_WALKING_SPEED);
	}
    
	else if (input == Input::PRESS_A)
	{
		if (mario.level == MARIO_LEVEL_RACOON)
		{
			CMarioState::spin.GetInstance()->isAttack = true;
			mario.ChangeState(CMarioState::spin.GetInstance());
			CMarioState::spin.GetInstance()->StartSpinning();
		}
	}
}



