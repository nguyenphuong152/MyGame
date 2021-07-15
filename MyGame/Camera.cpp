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
	this->width = width;
	this->height = height;
	
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
	//RenderBoundingBox();
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
	
	CGameObject::Update(dt);

	cam_center_X = x + width / 2 - MARIO_BIG_BBOX_WIDTH;
	cam_center_Y = y + height / 2 + MARIO_BIG_BBOX_WIDTH;

	if (y > HIDDEN_SCENE_Y && state == CAMERA_STATE_HIDDEN_SCENE) y = HIDDEN_SCENE_Y;
	  
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (player->state != MARIO_STATE_DIE && player->marioState != CMarioState::walking_overworld.GetInstance())
	{
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
					if (e->ny > 0)
					{
						isReachBoundaryTop = true;
						isReachBoundaryBottom = false;
					}
					else if (e->ny < 0)
					{
						isReachBoundaryBottom = true;
						isReachBoundaryTop = false;
					}
				}
				else if (e->nx != 0)
				{
					vx = player->vx;
					x += dx;
				}
				else if (e->ny != 0)
				{
					vy = player->vy;
					y += dy;
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else {
		InactiveCamera();
	}
}

void CCamera::FollowPlayerHorizontally()
{
	//DebugOut(L"startx %f ---- x %f --- camcentetr %f --- mario %f \n", start_x, x,cam_center_X,player->x);
	if ((player->vx > 0 && player->x < cam_center_X) // walk right
		|| (player->vx < 0 && player->x > cam_center_X))// walk left
	{
		vx = 0.0f;
	}
	else vx = player->vx;
}

void CCamera::FollowPlayerVertically()
{
	if (player->GetState() == CMarioState::fly.GetInstance()&& player->y<cam_center_Y)
	{
		vy = player->vy;
		isReachBoundaryBottom = false;
	}
	else if (isReachBoundaryBottom)
	{
		vy = 0;
	}
	else if (isReachBoundaryTop)
	{
		if (player->GetState() == CMarioState::drop.GetInstance() && player->y > cam_center_Y)
		{
			isReachBoundaryTop = false;
			vy = player->vy;
		}
		else if (player->isOnGround)
		{
			vy = 0;
		}
	}
	else if (!isReachBoundaryBottom && !isReachBoundaryTop)
	{
		if (player->isOnGround)
		{
			vy = 0;
		}
		else {
			vy = player->vy;
		}
	}
}

void CCamera::InactiveCamera()
{
	vx = 0;
	vy = 0;
}

void CCamera::InitCamera()
{
	player = CGame::GetInstance()->GetPlayer();
	float cx;
	cx = player->x - this->width / 2;

	if (cx < 0) cx = 22.0;

	isReachBoundaryBottom = true;

	SetPosition(cx, start_y);
	SetState(CAMERA_STATE_NORMAL);
}

void CCamera::AdjustPositionToHiddenScene()
{
	cam_old_x = x;
	cam_old_y = y;
	x = HIDDEN_SCENE_X;
	y = HIDDEN_SCENE_Y;
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y+45);
	SetState(CAMERA_STATE_HIDDEN_SCENE);
}

void CCamera::GoBackToNormal()
{
	x = cam_old_x;
	y = cam_old_y;
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
	SetState(CAMERA_STATE_NORMAL);
}