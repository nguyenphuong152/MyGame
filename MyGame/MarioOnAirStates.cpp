#include "MarioOnAirStates.h"
#include "Mario.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioStateSit.h"
#include "MarioStateStop.h"
#include "MarioStateRun.h"
#include "MarioStatePreFly.h"

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
}



