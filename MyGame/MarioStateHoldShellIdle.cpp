#include "MarioStateHoldShellIdle.h"
#include "Mario.h"

CMarioStateHoldShellIdle* CMarioStateHoldShellIdle::__instance = NULL;

CMarioStateHoldShellIdle::CMarioStateHoldShellIdle() {
	DebugOut(L"[STATE] create hodshell idle \n");
}

void CMarioStateHoldShellIdle::Enter(CMario& mario)
{
	mario.SetVelocityX(0);
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_IDLE);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_IDLE);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_IDLE);
	}
}
void CMarioStateHoldShellIdle::HandleInput(CMario& mario, Input input)
{
	CMarioHoldingShellStates::HandleInput(mario, input);
}

void CMarioStateHoldShellIdle::Update(DWORD dt, CMario& mario)
{
	
}


CMarioStateHoldShellIdle* CMarioStateHoldShellIdle::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateHoldShellIdle();
	return __instance;
}
