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
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_DROP);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_DROP);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON) {
		if (mario.isFloating)
		{
			mario.SetAnimation(MARIO_ANI_RACCOON_DROP_FLY);
		}
		else {
			mario.SetAnimation(MARIO_ANI_RACCOON_DROP);
		}
	}
	else if (marioLevel == MARIO_LEVEL_IMMORTAL)
	{
		mario.SetAnimation(MARIO_ANI_IMMORTAL_JUMP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_DROP);
	}
}
void CMarioStateDrop::HandleInput(CMario& mario, Input input)
{
	if (input == Input::PRESS_S && mario.GetLevel() == MARIO_LEVEL_RACOON&& mario.isOnMagicBlock == false)
	{
		mario.isFloating = true;
		mario.SetVelocityY(-MARIO_SPEED_Y_WHEN_FLOATING);
	}

	if (input == Input::PRESS_S && mario.isOnMagicBlock == true)
	{
		SetStateJumping(mario);
	}
	CMarioOnAirStates::HandleInput(mario, input);
}

void CMarioStateDrop::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.isOnRedMagicBlock = false;
		mario.canGoIntoPipe = false;
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateDrop* CMarioStateDrop::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateDrop();
	return __instance;
}
