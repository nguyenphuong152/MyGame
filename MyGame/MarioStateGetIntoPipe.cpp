#include "MarioStateGetIntoPipe.h"
#include "MarioStateWalk.h"
#include "MarioStateJump.h"
#include "MarioOnGroundStates.h"
#include "Mario.h"

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::__instance = NULL;

CMarioStateGetIntoPipe::CMarioStateGetIntoPipe() {
	DebugOut(L"[STATE] create go to pipe \n");
}

void CMarioStateGetIntoPipe::Enter(CMario& mario)
{
	mario.vx = 0;
	if (isTouchHiddenPipe) mario.SetAnimation(MARIO_ANI_DROP_FROP_PIPE);
    else mario.SetAnimation(MARIO_ANI_GET_INTO_PIPE);
}

void CMarioStateGetIntoPipe::HandleInput(CMario& mario, Input input)
{

}

void CMarioStateGetIntoPipe::Update(DWORD dt, CMario& mario)
{
	mario.vy = 0.2f;
	if (isTouchHiddenPipe) mario.vy = 0.8f;
}

CMarioStateGetIntoPipe* CMarioStateGetIntoPipe::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateGetIntoPipe();
	return __instance;
}
