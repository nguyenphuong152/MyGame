#include "Mario.h"
#include "MarioStateJump.h"
#include "MarioStateDrop.h"


CMarioStateJump* CMarioStateJump::__instance = NULL;

CMarioStateJump::CMarioStateJump() {
	DebugOut(L"[STATE] create jump \n");

}

void CMarioStateJump::Enter(CMario& mario)
{
	mario.isOnGround = false;
	SetCurrentState(MarioStates::JUMP);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_JUMP);
	}
	else if(mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_JUMP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_JUMP);
	}
}
void CMarioStateJump::HandleInput(CMario& mario,Input input)
{

	if (input == Input::RELEASE_S)
	{
		mario.canFlyHigh = false;
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
	//nếu sau khoảng thời gian cho nhảy cờ canFLyhigh còn bật thì tắt cờ đổi state drop
	else if ((GetTickCount() - mario.highjump_start > MAX_TIME_JUMP)&&mario.canFlyHigh)
	{
		mario.highjump_start = 0;
		mario.canFlyHigh = false;
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
	CMarioOnAirStates::HandleInput(mario,  input);
}

void CMarioStateJump::Update(DWORD dt, CMario& mario)
{

	//nếu nhảy một khoảng thời gian bật cờ canFlyHigh
	//từ đó mario có thể nhảy cao khi nhấn giữ S
	if ((GetTickCount() - mario.highjump_start > AVERAGE_TIME_JUMP)&&!mario.canFlyHigh)
	{
		mario.canFlyHigh = true;
	}

	if(mario.canFlyHigh)
	{
		mario.SetVelocityY(-MARIO_JUMP_HIGH_SPEED_Y);
	}


	if (mario.vy > 0)
	{
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
}

CMarioStateJump* CMarioStateJump::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateJump();
	return __instance;
}
