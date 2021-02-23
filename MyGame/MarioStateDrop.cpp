#include "Mario.h"
#include "MarioStateDrop.h"
#include "MarioStateIdle.h"
#include "MarioStateWalk.h"

CMarioStateDrop* CMarioStateDrop::__instance = NULL;

CMarioStateDrop::CMarioStateDrop() {
	DebugOut(L"[STATE] create drop \n");

}

void CMarioStateDrop::Enter(CMario& mario)
{
	mario.isOnGround = false;
	SetCurrentState(MarioStates::JUMP);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_DROP);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		if (mario.isFloating)
		{
			mario.SetAnimation(MARIO_ANI_RACCOON_DROP_FLY);
		}
		else {
			mario.SetAnimation(MARIO_ANI_RACCOON_DROP);
		}
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_DROP);
	}
}
void CMarioStateDrop::HandleInput(CMario& mario, Input input)
{
	if (input == Input::PRESS_S && mario.level == MARIO_LEVEL_RACOON)
	{
		mario.isFloating = true;
		mario.SetVelocityY(-MARIO_SPEED_Y_WHEN_FLOATING);
	}
	CMarioOnAirStates::HandleInput(mario, input);
}

void CMarioStateDrop::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateDrop* CMarioStateDrop::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateDrop();
	return __instance;
}
