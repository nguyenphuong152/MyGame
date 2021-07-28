#include "MarioState.h"
#include  "MarioStateGetIntoPipe.h"
#include "MarioOverworldState.h"
CMarioState::CMarioState()
{
	//this->currentState = CMarioState::IDLE;
}

void CMarioState::GetBoundingBox(CMario& mario,float& l, float& t, float& r, float& b)
{
	l = mario.x;
	t = mario.y;

	if (mario.GetLevel() == MARIO_LEVEL_BIG || mario.GetLevel() == MARIO_LEVEL_FIRE)
	{
		r = l + MARIO_BIG_BBOX_WIDTH;
		b = t + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACOON) {
		r = l + MARIO_RACOON_BBOX_WIDTH;
		b = t + MARIO_RACOON_BBOX_HEIGHT;

		if (mario.nx == -1)
		{
			r = l + MARIO_RACOON_BBOX_WIDTH - 10;
		}
	}
	else {
		r = l + MARIO_SMALL_BBOX_WIDTH;
		b = t + MARIO_SMALL_BBOX_HEIGHT;
	}
}


//CMarioState::CMarioState(CMarioState::MarioStates currentState)
//{
//	this->currentState = currentState;
//}
