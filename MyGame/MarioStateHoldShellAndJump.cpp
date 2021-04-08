#include "Mario.h"
#include "MarioStateHoldShellAndJump.h"
#include "MarioStateHoldShellAndDrop.h"


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
	else if (mario.level == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_JUMP_DROP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP);
	}
}
void CMarioStateHoldShellAndJump::HandleInput(CMario& mario, Input input)
{
	if (input == Input::RELEASE_S)
	{
		mario.canJumpHigh = false;
	}
	CMarioHoldingShellStates::HandleInput(mario, input);
}

void CMarioStateHoldShellAndJump::Update(DWORD dt, CMario& mario)
{
	if (mario.canJumpHigh)
	{
		if (GetTickCount64() - _jumpingStart > MARIO_JUMP_TIME)
		{
			mario.canJumpHigh = false;
		}
		else {
			mario.vy = -MARIO_JUMP_SPEED_Y;
		}
	}
	else if (mario.vy > 0)
	{
		mario.ChangeState(CMarioState::holdshell_drop.GetInstance());
	}
}

CMarioStateHoldShellAndJump* CMarioStateHoldShellAndJump::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateHoldShellAndJump();
	return __instance;
}
