#include "MarioStatePreFly.h"
#include "MarioStateFly.h"
#include "MarioStateRun.h"
#include "Mario.h"

CMarioStatePreFly* CMarioStatePreFly::__instance = NULL;

CMarioStatePreFly::CMarioStatePreFly() {
	DebugOut(L"[STATE] create pre-fly \n");
}

void CMarioStatePreFly::Enter(CMario& mario)
{
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_PRE_FLY);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_PRE_FLY);
	}
	else if (mario.level == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_PRE_FLY);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_PRE_FLY);
	}
}
void CMarioStatePreFly::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	
	if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT)) {
		if (input == Input::PRESS_S)
		{
				mario.isOnGround = false;
				mario.SetVelocityY(-MARIO_START_FLYING_SPEED);
				mario.ChangeState(CMarioState::fly.GetInstance());
		}
	}
	else {
		mario.powerMode = false;
		mario.ChangeState(CMarioState::run.GetInstance());
	}
}

void CMarioStatePreFly::Update(DWORD dt, CMario& mario)
{

}


CMarioStatePreFly* CMarioStatePreFly::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStatePreFly();
	return __instance;
}
