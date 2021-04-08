#include "Mario.h"
#include "MarioStateHoldShellAndDrop.h"
#include "MarioStateHoldShellIdle.h"
#include "MarioStateDrop.h"


CMarioStateHoldShellAndDrop* CMarioStateHoldShellAndDrop::__instance = NULL;

CMarioStateHoldShellAndDrop::CMarioStateHoldShellAndDrop() {
	DebugOut(L"[STATE] create drop shell \n");

}

void CMarioStateHoldShellAndDrop::Enter(CMario& mario)
{
	CMarioStateHoldShellAndJump::Enter(mario);
}
void CMarioStateHoldShellAndDrop::HandleInput(CMario& mario, Input input)
{

	if (input == Input::RELEASE_S)
	{
		mario.canJumpHigh = false;
		mario.ChangeState(CMarioState::holdshell_drop.GetInstance());
	}
	//nếu sau khoảng thời gian cho nhảy cờ canJumpHigh còn bật thì tắt cờ đổi state drop
	/*else if ((GetTickCount() - mario.highjump_start > MAX_TIME_JUMP) && mario.canJumpHigh)
	{
		mario.canJumpHigh = false;
		mario.ChangeState(CMarioState::holdshell_drop.GetInstance());
	}*/

	CMarioHoldingShellStates::HandleInput(mario, input);
}

void CMarioStateHoldShellAndDrop::Update(DWORD dt, CMario& mario)
{
	if (mario.isOnGround)
	{
		mario.ChangeState(CMarioState::holdshell_idle.GetInstance());
	}
}

CMarioStateHoldShellAndDrop* CMarioStateHoldShellAndDrop::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateHoldShellAndDrop();
	return __instance;
}
