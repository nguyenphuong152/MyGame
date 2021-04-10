#include "MarioStateHoldShellAndRun.h"
#include "MarioStateHoldShellIdle.h"
#include "Mario.h"

CMarioStateHoldShellAndRun* CMarioStateHoldShellAndRun::__instance = NULL;

CMarioStateHoldShellAndRun::CMarioStateHoldShellAndRun() {
	DebugOut(L"[STATE] create hold shell run \n");
}

void CMarioStateHoldShellAndRun::Enter(CMario& mario)
{
	if (mario.level == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_HANDLESHELL_RUN);
	}
	else if (mario.level == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_HANDLESHELL_RUN);
	}
	else if (mario.level == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_HANDLESHELL_RUN);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_HANDLESHELL_RUN);
	}
}
void CMarioStateHoldShellAndRun::HandleInput(CMario& mario, Input input)
{
	CMarioHoldingShellStates::HandleInput(mario, input);
}

void CMarioStateHoldShellAndRun::Update(DWORD dt, CMario& mario)
{
	if (mario.vx > 0) {
		mario.vx += -0.0004 * dt;
		if (mario.vx < 0) {
			mario.ChangeState(CMarioState::holdshell_idle.GetInstance());
		}
	}
	else if (mario.vx < 0) {
		mario.vx += 0.0004 * dt;
		if (mario.vx > 0) {
				mario.ChangeState(CMarioState::holdshell_idle.GetInstance());
		}
	}

}


CMarioStateHoldShellAndRun* CMarioStateHoldShellAndRun::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateHoldShellAndRun();
	return __instance;
}
