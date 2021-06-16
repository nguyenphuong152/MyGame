#include "Camera.h"
#include "Game.h"
#include "Utils.h"
#include "Boundary.h"
#include "MarioStateFly.h"
#include "MarioStateDrop.h"
#include "MarioStateJump.h"
#include "Pipe.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"
#include "HUD.h"

CCamera* CCamera::__instance = NULL;

void CCamera::SetProperty(float l, float t, float width, float height)
{
	x = l;
	y = t;
	this->width = width;
	this->height = height;
	cam_center_X = x+width/ 2;
	cam_center_Y = y+height/2;
	isEnable = true;
	isReachBoundaryBottom = true;
	player = CMario::GetInstance();
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
	//RenderBoundingBox();
}

CCamera* CCamera::GetInstance()
{
	if (__instance == NULL) __instance = new CCamera();
	return __instance;
}

void CCamera::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	CGameObject::Update(dt);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CGame* game = CGame::GetInstance();

	if (player->state != MARIO_STATE_DIE)
	{
		FollowPlayerHorizontally();
		FollowPlayerVertically();

		cam_center_X = x  + width / 2;
		cam_center_Y = y  + height/ 2;

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
					else if (e->nx > 0) {
						isReachBoundaryLeft = true;
					}

					if (e->ny < 0)
					{
						isReachBoundaryBottom = true;
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
		game->SetCamPos(x, y);
	}
	else {
		InactiveCamera();
	}
}

void CCamera::FollowPlayerHorizontally()
{
	if (!isReachBoundaryLeft && !isReachBoundaryRight)
	{
		if (player->x > cam_center_X && player->vx > 0 || player->x < cam_center_X && player->vx < 0)
		{
			vx = player->vx;
		}
		else if (player->vx == 0)
		{
			vx = 0;
		}
	}
	else {
		if (isReachBoundaryRight && player->x < cam_center_X && player->vx < 0 || isReachBoundaryLeft && player->x > cam_center_X && player->vx > 0)
		{
			vx = player->vx;
			isReachBoundaryLeft = isReachBoundaryRight = false;
		}
	}
}

void CCamera::FollowPlayerVertically()
{
	if (player->GetState() == CMarioState::fly.GetInstance())
	{
	    if (isReachBoundaryBottom == true && player->vy > 0)
		{
			vy = 0;
		}
		else if (player->y < cam_center_Y)
		{
			isReachBoundaryBottom = false;
			vy = player->vy;
		}
	}
	else if (player->GetState() == CMarioState::drop.GetInstance() && player->y > cam_center_Y|| player->GetState() == CMarioState::jump.GetInstance() && player->y < cam_center_Y)
	{
		if (!isReachBoundaryBottom) vy = player->vy;
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
	CGame::GetInstance()->SetCamPos(x, y);
}

void CCamera::GoBackToNormal()
{
	x = cam_old_x;
	y = cam_old_y;
	HUD::GetInstance()->SetPosition(HUD_POSITION_Y);
	CGame::GetInstance()->SetCamPos(x, y);
}
