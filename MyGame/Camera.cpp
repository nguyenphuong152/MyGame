#include "Camera.h"
#include "Game.h"
#include "Utils.h"
#include "Boundary.h"
#include "MarioStateFly.h"
#include "MarioStateDrop.h"
#include "MarioStateJump.h"
#include "MarioOverworldState.h"
#include "Pipe.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"
#include "HUD.h"

CCamera* CCamera::__instance = NULL;

void CCamera::SetProperty(float y,float width, float height)
{
	this->width = CAM_WIDTH;
	this->height = CAM_HEIGHT;
	
	isEnable = true;

	start_y = y;

	InitCamera();
}

void CCamera::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CCamera::Render()
{
	//DebugOut(L"cam y %f \n", y);
	RenderBoundingBox();
}

void CCamera::SetState(int state)
{
	CGameObject::SetState(state);
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

void CCamera::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	
	if (player == NULL) return;

	CGameObject::Update(dt);

	if (y > HIDDEN_SCENE_Y && state == CAMERA_STATE_HIDDEN_SCENE1) y = HIDDEN_SCENE_Y;
	  
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (player->state != MARIO_STATE_DIE && player->marioState != CMarioState::walking_overworld.GetInstance())
	{
		cam_center_X = x + (width / 2 )- (MARIO_RACOON_BBOX_WIDTH/2);
		cam_center_Y = y + (height / 2) - (MARIO_RACOON_BBOX_HEIGHT/2);
        
		FollowPlayerHorizontally();
		FollowPlayerVertically();
		CalcPotentialCollisions(colObject, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0;
			float rdx = 0, rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBoundary*>(e->obj))
				{
					if (e->ny < 0)
					{
						isReachBoundaryBottom = true;
					}
				}
				else {
						if (e->nx != 0)
						{
							FollowPlayerHorizontally();
							x += dx;
						}
						if (e->ny != 0)
						{
							FollowPlayerVertically();
							y += dy;
						}
				}
				
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else {
		InactiveCamera();
	}
	//if (state == CAMERA_STATE_HIDDEN_SCENE) vy = 0;
}

void CCamera::FollowPlayerHorizontally()
{
	if (state == CAMERA_STATE_HIDDEN_SCENE3)
	{
		vx = CAMERA_AUTO_VELOCITY_X;
		player->MovingMarioWithCamera();
	}
	else {
		if ((player->vx > 0 && player->x < cam_center_X) // walk right
			|| (player->vx < 0 && player->x > cam_center_X))// walk left
		{
			vx = 0.0f;
		}
		else {
			vx = player->vx;
		}
	}
}

void CCamera::FollowPlayerVertically()
{
	if (state == CAMERA_STATE_HIDDEN_SCENE3)
	{
		vx = CAMERA_AUTO_VELOCITY_X;
		player->MovingMarioWithCamera();
	}
	
	if (player->GetState() == CMarioState::fly.GetInstance() && player->GetLevel() == MARIO_LEVEL_RACOON)
	{
		isReachBoundaryBottom = false;
	}

	if (isReachBoundaryBottom == false)
	{
		if ((player->vy < 0 && player->y < cam_center_Y) ||
			(player->vy > 0 && player->y > cam_center_Y))
		{
			vy = player->vy;
		}
		else {
			vy = 0.0f;
		}
	}
}

void CCamera::InactiveCamera()
{
	vx = 0.0f;
	vy = 0.0f;
}

void CCamera::InitCamera()
{
	player = CGame::GetInstance()->GetPlayer();
	float cx;
	cx = player->x - this->width / 2;

	if (cx < 0) cx = CAM_START_X;

	SetPosition(cx, start_y);
	//SetPosition(cx, HIDDEN_SCENE_Y_3);
	SetState(CAMERA_STATE_NORMAL);
}

void CCamera::AdjustPositionToHiddenScene()
{
	cam_old_x = x;
	cam_old_y = y;

	if (CGame::GetInstance()->current_scene == WORLD1_1_MAP)
	{
		x = HIDDEN_SCENE_X;
		y = HIDDEN_SCENE_Y;
		SetState(CAMERA_STATE_HIDDEN_SCENE1);
	}
	else if (CGame::GetInstance()->current_scene == WORLD1_3_MAP)
	{
		x = HIDDEN_SCENE_X_3;
		y = HIDDEN_SCENE_Y_3;
		SetState(CAMERA_STATE_HIDDEN_SCENE3);
	}
	SetPosition(x, y);
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y+45);
	
}

void CCamera::GoBackToNormal()
{
	if (CGame::GetInstance()->current_scene == WORLD1_1_MAP)
	{
		x = cam_old_x;
		y = cam_old_y;
	}
	else if (CGame::GetInstance()->current_scene == WORLD1_3_MAP)
	{
		y = 10;
		float cx = player->x - this->width / 2;
		isReachBoundaryBottom = false;
		SetPosition(cx, y);
	}

	//DebugOut(L"cam x player x %f %f\n", x, player->x);

	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
	SetState(CAMERA_STATE_NORMAL);
}