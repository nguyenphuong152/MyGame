#include "MarioOverworldState.h"
#include "MarioStateIdle.h"
#include "Mario.h"

CMarioOverworldState* CMarioOverworldState::__instance = NULL;

CMarioOverworldState::CMarioOverworldState() {
	scene_id = -1;
	DebugOut(L"[STATE] create idle \n");
}

void CMarioOverworldState::Enter(CMario& mario)
{
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_WALK_OW_SMALL);
	}
	else if (marioLevel == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_WALK_OW_RACCOON);
	}
	else {
		mario.SetAnimation(MARIO_ANI_WALK_OW_BIG);
	}
}
void CMarioOverworldState::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();

	if (input == Input::KEYSTATE)
	{
		mario.canChangeMap = false;
		if (game->IsKeyDown(DIK_LEFT)) {
			mario.vx = -MARIO_SPEED;
		}
		else if (game->IsKeyDown(DIK_RIGHT))
		{
			mario.vx = MARIO_SPEED;
		}
		else if (game->IsKeyDown(DIK_DOWN))
		{
			mario.vy = MARIO_SPEED;
		}
		else if (game->IsKeyDown(DIK_UP))
		{
			mario.vy = -MARIO_SPEED;
		}
	} 
}

void CMarioOverworldState::Update(DWORD dt, CMario& mario)
{
	if (scene_id != 0 && mario.canChangeMap == true)
	{
		 CGame::GetInstance()->SwitchScene(scene_id);
	}
}

void CMarioOverworldState::SetSceneSwitching(int scene_id)
{
	this->scene_id = scene_id;
}

void CMarioOverworldState::GetBoundingBox(CMario &mario,float& l, float& t, float& r, float& b)
{
	CMarioState::GetBoundingBox(mario,l, t, r, b);
	r = l + MARIO_OVERWORLD_BBOX_WIDTH;
	b = t + MARIO_OVERWORLD_BBOX_WIDTH;
}

CMarioOverworldState* CMarioOverworldState::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioOverworldState();
	return __instance;
}
