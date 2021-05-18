#include "MarioStateTransform.h"
#include "Mario.h"
#include "MarioStateIdle.h"

CMarioStateTransform* CMarioStateTransform::__instance = NULL;

CMarioStateTransform::CMarioStateTransform() {
	DebugOut(L"[STATE] create trtansform \n");
}

void CMarioStateTransform::Enter(CMario& mario)
{
	if (mario.GetLevel() == MARIO_LEVEL_BIG)
	{
		mario.SetAnimation(MARIO_ANI_ITEM_SMALL_TO_BIG);
	}
	else if(mario.GetLevel()==MARIO_LEVEL_RACOON) 
	{
		mario.SetAnimation(MARIO_ANI_ITEM_BIG_TO_RACOON);
	}
}
void CMarioStateTransform::HandleInput(CMario& mario, Input input)
{
	
}

void CMarioStateTransform::Update(DWORD dt, CMario& mario)
{
	if (GetTickCount64() - _transformStart > MARIO_TRANSFORM_TIME && isTransform == 1)
	{
		
		isTransform = 0;
		_transformStart = 0;
		
		mario.ChangeState(CMarioState::idle.GetInstance());
	}
}

CMarioStateTransform* CMarioStateTransform::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateTransform();
	return __instance;
}
