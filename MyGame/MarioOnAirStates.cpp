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
	if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT))
	{
		mario.SetVelocityX(mario.nx * MARIO_WALKING_SPEED);
		//mario.ChangeState(CMarioState::walk.GetInstance());
	}
}



