#include "Mario.h"
#include "MarioStateSit.h"
#include "MarioStateIdle.h"


CMarioStateSit* CMarioStateSit::__instance = NULL;

CMarioStateSit::CMarioStateSit() {
	DebugOut(L"[STATE] create jump \n");

}

void CMarioStateSit::Enter(CMario& mario)
{
	mario.isOnGround = true;
	mario.isSitting = true;
	SetCurrentState(MarioStates::SIT);
	if (mario.level == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_BIG_SIT);
	}
}
void CMarioStateSit::HandleInput(CMario& mario)
{
	CGame* game = CGame::GetInstance();
	if (!game->IsKeyDown(DIK_DOWN))
	{
		mario.isSitting = false;
		mario.y -= MARIO_BIG_BBOX_HEIGHT - MARIO_BIG_BBOX_SIT_HEIGHT;
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
	else
	{
		CMarioOnGroundStates::HandleInput(mario);
	}

}

void CMarioStateSit::Update(DWORD dt, CMario& mario)
{
}

CMarioStateSit* CMarioStateSit::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateSit();
	return __instance;
}
