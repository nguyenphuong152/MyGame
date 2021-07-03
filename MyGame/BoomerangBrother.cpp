#include "BoomerangBrother.h"
#include "ObjectBoundary.h"
#include "Utils.h"
#include "Ground.h"
#include "Boomerang.h"
#include "BoomerangPool.h"

CBoomerangBrother::CBoomerangBrother()
{
	nx = direction = -1;
	ny = 1;
	StartWalking();
	SetState(BOOMERANGBROTHER_STATE_WALKING);
}

void CBoomerangBrother::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + BOOMERANGBROTHER_BBOX_WIDTH;
	t = y;
	b = y + BOOMERANGBROTHER_BBOX_HEIGHT;
}

void CBoomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CEnemy::Update(dt, coObjects);

	vy += BOOMERANGBROTHER_GRAVITY * dt;

	if (isOnGround && GetTickCount64() - _startWalking > WALKING_TIME)
	{
		SetState(BOOMERANGBROTHER_STATE_JUMPING);
	}
	
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0, rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//day object ra mot khoang de k bi chong va cham
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0 && isOnGround == false)
				{
					StartWalking();
					SetState(BOOMERANGBROTHER_STATE_WALKING);
				}
			}
			else if (dynamic_cast<CObjectBoundary*>(e->obj))
			{
				if (e->nx != 0)
				{
					direction = -direction;
					vx = BOOMERANGBROTHER_WALKING_SPEED * direction;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerangBrother::Render()
{
	int ani = BOOMERANGBROTHER_ANI_WALKING;
	/*if (state == BOOMERANGBROTHER_STATE_JUMPING)
		ani = BOOMERANGBROTHER_ANI_JUMPING;*/

	//change direction for koopas
	animation_set->at(ani)->Render(nx, ny, x, y);
	RenderBoundingBox();
}


void CBoomerangBrother::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == BOOMERANGBROTHER_STATE_WALKING) vx = BOOMERANGBROTHER_WALKING_SPEED* direction;
	else if(state == BOOMERANGBROTHER_STATE_JUMPING){
		CBoomerang* bmr = CBoomerangPool::GetInstance()->Create();
		if (bmr != NULL)
		{
			bmr->StartThrowing(this);
		}

		ResetWalking();
		vy = -BOOMERANGBROTHER_DEFLECT_SPEED;
	}
}
