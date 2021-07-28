#include "IntroScene.h"
#include "Game.h"
#include "MarioStateWalk.h"
#include "MarioStateIdle.h"
#include "MarioStateSit.h"
#include "MarioStateJump.h"
#include "MarioStateDrop.h"


IntroScene* IntroScene::__instance = NULL;

IntroScene* IntroScene::GetInstance()
{
	if (__instance == NULL) __instance = new IntroScene();
	return __instance;
}

void IntroScene::Init(vector<LPGAMEOBJECT> &objects, CMap* map)
{
	this->map = map;

	InitMario();
	cam = new CCamera(0.0f, (float)CAM_WIDTH, (float)CAM_HEIGHT);
	cam->SetPosition(0.0f, 0.0f);
	CGame::GetInstance()->SetMainCamera(cam);

	curtain = new CCurtain();
	curtain->SetPosition(0.0f, 0.0f);

	curtain_super_bros = new CCurtain();
	curtain_super_bros->SetPosition(0.0f, -500.0f);
	curtain_super_bros->SetState(CURTAIN_STATE_SUPER_BROS);

	curtain_three = new CCurtain();
	curtain_three->SetPosition(350, -130.0f);
	curtain_three->SetState(CURTAIN_STATE_THREE);

	arrow = new CArrow();
	arrow->SetPosition(205, 425);
	arrow->start_y = 425;

	objects.push_back(first_mario);
	objects.push_back(second_mario);
}

void IntroScene::InitMario()
{
	second_mario = new CMario(0.0f, 315.0f);
	first_mario = new CMario((float)(CAM_WIDTH - 55), 300.0f);
	first_mario->nx = -1;
	isJump = false;

	second_mario->SetLevel(MARIO_LEVEL_BIG);
	first_mario->SetLevel(MARIO_LEVEL_BIG);

	first_mario->SetObjectAnimation(1);
	second_mario->SetObjectAnimation(1);
	CGame::GetInstance()->SetMainPlayer(first_mario);
	StartWalking();
}

void IntroScene::UpdateMarios(DWORD dt)
{
	if (isWalk == true && GetTickCount64() - walking_start > 2000)
	{
		ResetWalking();
		first_mario->isAutoWalk = true;
		second_mario->isAutoWalk = true;
	}

	if (first_mario->isAutoWalk && second_mario->isAutoWalk)
	{
		first_mario->vx = -MARIO_WALKING_SPEED / 1.2f;
		second_mario->vx = MARIO_WALKING_SPEED / 1.2f;
		first_mario->ChangeState(CMarioState::walk.GetInstance());
		second_mario->ChangeState(CMarioState::walk.GetInstance());
	}

	if ((first_mario->x < CAM_WIDTH / 2) && (second_mario->x > CAM_WIDTH / 2 - 100))
	{
		first_mario->isAutoWalk = false;
		second_mario->isAutoWalk = false;

		second_mario->vy = -MARIO_JUMP_SPEED_Y;
		first_mario->ChangeState(CMarioState::idle.GetInstance());
		second_mario->ChangeState(CMarioState::jump.GetInstance());
	}

	if (second_mario->y < -100)
	{
		second_mario->isEnable = false;
		curtain->SetState(SHORT_CURTAIN);
		curtain->SetPosition(0, 0);
		curtain_super_bros->isShowing = true;
		curtain_three->isShowing = true;
		CGame::GetInstance()->SetBackgroundColor(BACKGROUND_COLOR_SHOWCASE);
	}

	if (curtain_three->showcase)
	{
		first_mario->vx = -MARIO_WALKING_SPEED / 1.2f;
		first_mario->ChangeState(CMarioState::walk.GetInstance());
	}

	second_mario->marioState->Enter(*second_mario);
	first_mario->marioState->Enter(*first_mario);
}

void IntroScene::Update(DWORD dt,vector<LPGAMEOBJECT>* coObjects)
{
	if (first_mario == NULL && second_mario == NULL) return;

	first_mario->Update(dt,coObjects);
	second_mario->Update(dt, coObjects);
	CGame::GetInstance()->GetMainCamera()->Update(dt, coObjects);
	curtain->Update(dt, coObjects);
	curtain_super_bros->Update(dt, coObjects);
	curtain_three->Update(dt, coObjects);
	arrow->Update(dt, coObjects);

	UpdateMarios(dt);

	if (arrow->startGame) {
		first_mario->SwitchOverworld();
		first_mario->isEnable = false;
	}

	if (first_mario->isEnable == false && second_mario->isEnable == false)
		return;
}

void IntroScene::Render()
{
	if (first_mario->isEnable == false && second_mario->isEnable == false)
		return;

	map->RenderMap();

	if (curtain_three->showcase)
	{
		CSprites::GetInstance()->Get(CLOUD_SMALL)->Draw(-1, 1, 50, 80);
		CSprites::GetInstance()->Get(CLOUD_BIG)->Draw(-1, 1, 50, 300);
		CSprites::GetInstance()->Get(CLOUD_BIG)->Draw(-1, 1, CAM_WIDTH - 200, 80);
		CSprites::GetInstance()->Get(TREE_LEFT)->Draw(-1, 1, CAM_WIDTH - 205, 260);
		CSprites::GetInstance()->Get(TREE_RIGHT)->Draw(-1, 1, -5, 360);
		CSprites::GetInstance()->Get(PLAYER_GAME)->Draw(-1, 1, 240, 430);
		arrow->Render();
	}

	first_mario->Render();
	second_mario->Render();
	
	curtain_three->Render();
	curtain_super_bros->Render();
	curtain->Render();

	
}

void IntroScene::Clear()
{
	cam = NULL;
	map = NULL;
	first_mario = NULL;
	second_mario = NULL;
	curtain = NULL;
	curtain_super_bros = NULL;
	curtain_three = NULL;
	arrow = NULL;
}


