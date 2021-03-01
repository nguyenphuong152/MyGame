#include "Mario.h"
#include "MarioStateHoldShellAndJump.h"
#include "MarioStateHoldShellAndDrop.h"
#include "MarioStateDrop.h"


CMarioStateHoldShellAndJump* CMarioStateHoldShellAndJump::__instance = NULL;

CMarioStateHoldShellAndJump::CMarioStateHoldShellAndJump() {
	DebugOut(L"[STATE] create jump shell \n");

}

void CMarioStateHoldShellAndJump::Enter(CMario& mario)
{
	mario.isOnGround = false;
	SetCurrentState(MarioStates::HOLDSHELL_JUMP);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP);
	}
}
void CMarioStateHoldShellAndJump::HandleInput(CMario& mario, Input input)
{
	CMarioHoldingShellStates::HandleInput(mario, input);
}

void CMarioStateHoldShellAndJump::Update(DWORD dt, CMario& mario)
{

	//nếu nhảy một khoảng thời gian bật cờ canFlyHigh
	//từ đó mario có thể nhảy cao khi nhấn giữ S
	if ((GetTickCount() - mario.highjump_start > AVERAGE_TIME_JUMP) && !mario.canFlyHigh)
	{
		mario.canFlyHigh = true;
	}

	if (mario.canFlyHigh)
	{
		mario.SetVelocityY(-MARIO_JUMP_HIGH_SPEED_Y);
	}


	if (mario.vy > 0)
	{
		mario.ChangeState(CMarioState::holdshell_drop.GetInstance());
	}
}

CMarioStateHoldShellAndJump* CMarioStateHoldShellAndJump::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateHoldShellAndJump();
	return __instance;
}
