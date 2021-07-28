#include "MarioStateTransformLevelDown.h"
#include "Mario.h"
#include "MarioStateIdle.h"

CMarioStateTransformLevelDown* CMarioStateTransformLevelDown::__instance = NULL;

CMarioStateTransformLevelDown::CMarioStateTransformLevelDown() {
	_transformStart = 0;
	isTransform = 0;
	DebugOut(L"[STATE] create trtansformdown \n");
}

void CMarioStateTransformLevelDown::Enter(CMario& mario)
{
	if (mario.GetLevel() == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_ITEM_SMALL_TO_BIG);
	}
	else if (mario.GetLevel() == MARIO_LEVEL_RACOON)
	{
		mario.SetAnimation(MARIO_ANI_ITEM_BIG_TO_RACOON);
	}
}
void CMarioStateTransformLevelDown::HandleInput(CMario& mario, Input input)
{

}

void CMarioStateTransformLevelDown::Update(DWORD dt, CMario& mario)
{
	mario.vx = 0;
	if (GetTickCount64() - _transformStart > MARIO_TRANSFORM_TIME && isTransform == 1)
	{
		isTransform = 0;
		_transformStart = 0;
		mario.SetLevel(mario.GetLevel() - 1);
		if (mario.GetLevel() == MARIO_LEVEL_RACOON)  mario.tail->isEnable = true;

		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateTransformLevelDown* CMarioStateTransformLevelDown::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateTransformLevelDown();
	return __instance;
}
