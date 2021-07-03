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

void CCamera::SetProperty(float l, float t, float width, float height)
{
	//sua start_x neu vi tri cam thay doi
	x = start_x = l ;

    //xoa line nay
	start_x = 3;

	y = start_y= t ;
	this->width = width;
	this->height = height;
	cam_center_X = x+width/ 2-10;
	cam_center_Y = y+height/2;
	isEnable = true;
	player = CGame::GetInstance()->GetPlayer();
	SetState(CAMERA_STATE_NORMAL);
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

	if (y > start_y && state == CAMERA_STATE_NORMAL) y = start_y;
	else if (y > HIDDEN_SCENE_Y && state == CAMERA_STATE_HIDDEN_SCENE) y = HIDDEN_SCENE_Y;
	else if (x < start_x) x = start_x;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();


	if (player->state != MARIO_STATE_DIE && player->marioState!=CMarioState::walking_overworld.GetInstance())
	{
		cam_center_X = x + width / 2 - 10;
		cam_center_Y = y + height / 2;

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

			x += min_tx * dx + 0.4f;
			y += min_ty * dy + 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBoundary*>(e->obj))
				{
					if (e->nx < 0)
					{
						isReachBoundaryRight = true;
					}
				}
				else if (e->nx != 0) //neu dung nhung objects khac thi di tiep
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
	if (x>start_x && !isReachBoundaryRight)
	{
		if (player->x > cam_center_X && player->vx > 0 || player->x < cam_center_X && player->vx < 0)
		{
			vx = player->vx;
		}
		else 
		{
			vx = 0;
		}
	}
	else if (isReachBoundaryRight && player->x < cam_center_X && player->vx < 0 || x==start_x && player->x > cam_center_X && player->vx > 0)
		{
			vx = player->vx;
			isReachBoundaryRight = false;
		}
}

void CCamera::FollowPlayerVertically()
{
	
	if (player->GetState() == CMarioState::fly.GetInstance())
	{
	    if (y == start_y && player->vy > 0)
		{
			vy = 0;
		}
		else if (player->y < cam_center_Y)
		{
			vy = player->vy;
		}
	}
	else if (player->GetState() == CMarioState::drop.GetInstance()&&player->y > cam_center_Y || player->GetState() == CMarioState::jump.GetInstance() && player->y < cam_center_Y)
	{
		if (y < start_y) {
			vy = player->vy;
		}
		else if (player->isOnGround)
		{
			vy = 0;
		}
	}
	else if (player->isOnGround)
	{
		vy = 0;
	}
}

void CCamera::InactiveCamera()
{
	vx = 0;
	vy = 0;
}

void CCamera::AdjustPositionToHiddenScene()
{
	cam_old_x = x;
	cam_old_y = y;
	x = HIDDEN_SCENE_X;
	y = HIDDEN_SCENE_Y;
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y-35);
	SetState(CAMERA_STATE_HIDDEN_SCENE);
}

void CCamera::GoBackToNormal()
{
	x = cam_old_x;
	y = cam_old_y;
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
	SetState(CAMERA_STATE_NORMAL);
}
