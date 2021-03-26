#include "MarioStatePreFly.h"
#include "MarioStateFly.h"
#include "Mario.h"

CMarioStatePreFly* CMarioStatePreFly::__instance = NULL;

CMarioStatePreFly::CMarioStatePreFly() {
	DebugOut(L"[STATE] create pre-fly \n");
}

void CMarioStatePreFly::Enter(CMario& mario)
{
	SetCurrentState(MarioStates::PRE_FLY);
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
	if (mario.power==72||mario.powerMode)
	{
		if (game->IsKeyDown(DIK_LEFT) || game->IsKeyDown(DIK_RIGHT)) {
			if (input == Input::PRESS_S)
			{
				mario.isOnGround = false;
				mario.SetVelocityY(-MARIO_JUMP_HIGH_SPEED_Y);
				mario.ChangeState(CMarioState::fly.GetInstance());
			}
			else
			{
				mario.SetVelocityX(mario.nx * MARIO_PRE_FLYING_SPEED);
				mario.ChangeState(CMarioState::pre_fly.GetInstance());
			}
		}
	}
	else {

		CMarioOnGroundStates::HandleInput(mario, input);
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
