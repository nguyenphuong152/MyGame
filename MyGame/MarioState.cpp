#include "MarioState.h"
#include  "MarioStateGetIntoPipe.h"
#include "MarioOverworldState.h"
CMarioState::CMarioState()
{
	//this->currentState = CMarioState::IDLE;
}

void CMarioState::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CMario* mario = CGame::GetInstance()->GetPlayer();
	l = mario->x;
	t = mario->y;
	if (mario->GetLevel() == MARIO_LEVEL_BIG || mario->GetLevel() == MARIO_LEVEL_FIRE)
	{
		r = mario->x + MARIO_BIG_BBOX_WIDTH;
		b = mario->y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (mario->GetLevel() == MARIO_LEVEL_RACOON || mario->GetLevel() == MARIO_LEVEL_IMMORTAL) {
		r = mario->x + MARIO_RACOON_BBOX_WIDTH;
		b = mario->y + MARIO_RACOON_BBOX_HEIGHT;

		if (mario->nx == -1)
		{
			r = mario->x + MARIO_RACOON_BBOX_WIDTH - 10;
		}
	}
	else {
		r = mario->x + MARIO_SMALL_BBOX_WIDTH;
		b = mario->y + MARIO_SMALL_BBOX_HEIGHT;
	}

	if (mario->isSitting)
	{
		b = mario->y + MARIO_BIG_BBOX_SIT_HEIGHT;
	}
	else if (mario->GetState() == CMarioState::go_to_pipe.GetInstance())
	{
		l = mario->x - 60;
		r = mario->x + MARIO_BIG_BBOX_WIDTH - 12;
	}
	else if (mario->GetState() == CMarioState::walking_overworld.GetInstance())
	{
		r = mario->x + MARIO_SMALL_BBOX_WIDTH + 8;
		b = mario->y + MARIO_SMALL_BBOX_HEIGHT - 2;
	}
}

//CMarioState::CMarioState(CMarioState::MarioStates currentState)
//{
//	this->currentState = currentState;
//}
