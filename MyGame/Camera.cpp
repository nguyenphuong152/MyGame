#include "Camera.h"
#include "Game.h"
#include "Utils.h"
#include "Boundary.h"
#include "MarioStateFly.h"
#include "MarioStateDrop.h"
#include "Pipe.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"

CCamera* CCamera::__instance = NULL;

void CCamera::SetProperty(float l, float t, float width, float height)
{
	//player = NULL;
	x = l;
	y = t;
	this->width = width;
	this->height = height;
	cam_center_X = (x+x+width) / 2;
	cam_center_Y = (y+y+height)/2;
	isEnable = true;
	isOnGround = false;
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
	RenderBoundingBox();
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

	if(!isOnGround) vy += 0.0015 * dt;

	coEvents.clear();

	CGame* game = CGame::GetInstance();

	FollowPlayerHorizontally();

	if (player->GetState() == CMarioState::fly.GetInstance()&& player->y<cam_center_Y)
	{
		isOnGround = false;
		vy = player->vy;
	}

	cam_center_X = (x + x + width) / 2;
	cam_center_Y = (y + y + height) / 2;
	//DebugOut(L"Cam ceneter %f \n", cam_center_X);

	CalcPotentialCollisions(colObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
	//DebugOut(L"vo else \n");
	float min_tx, min_ty, nx = 0, ny = 0;
	float rdx = 0, rdy = 0;

	FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx +0.4f;
		y += min_ty * dy +0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj)||dynamic_cast<CBox*>(e->obj)||dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0) {
					x += dx;
				}
			}
			else if (dynamic_cast<CBoundary*>(e->obj))
			{
				if (e->nx < 0)
				{
					isReachBoundaryRight = true;
				}
				else if(e->nx>0){
					isReachBoundaryLeft = true;
				}

				if (e->ny > 0)
				{
					vy = player->vy;
				}
				else if (e->ny < 0)
				{
					isOnGround = true;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	game->SetCamPos(x,y);
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