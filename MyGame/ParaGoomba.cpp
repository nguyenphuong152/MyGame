#include "ParaGoomba.h"
#include "Utils.h"
#include "Brick.h"
#include "Ground.h"

CParaGoomba::CParaGoomba()
{
	isEnable = true;
	jumpingTimes = 0;
	SetAnimation(PARA_GOOMBA_ANI);
	SetState(PARA_GOOMBA_STATE_WALKING);
	SetLevel(PARA_GOOMBA_LEVEL_2);
}

void CParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{ 
	CGoomBa::GetBoundingBox(l, t, r, b);
	if (level == PARA_GOOMBA_LEVEL_2)
	{
		if (state == PARA_GOOMBA_STATE_WALKING)
		{
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT - 5;
		}
		else {
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT;
		}
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	vy += 0.0015f * dt;

	if (walking == 1 && GetTickCount64() - walking_start > PARA_GOOMBA_WALKING_TIME)
	{
		walking = 0;
	}

	if (isOnGround && walking == 0)
	{
		SetState(PARA_GOOMBA_STATE_FLY);
		jumpingTimes += 1;
	}

	if (GetTickCount64() - die_start > GOOMBA_DIE_TIME && die) isEnable = false;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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

		//day object ra mot khoang de k bi chong va cham
		x += min_tx * dx + nx * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					this->nx = -this->nx;
					vx = this->nx * GOOMBA_WALKING_SPEED;
				}

			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
				}
			}
		}
	}

	//DebugOut(L"[INFO]vy: %f \n", vy);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CParaGoomba::Render()
{
	int ani = -1;
	if (level == PARA_GOOMBA_LEVEL_2)
	{
		if (state == PARA_GOOMBA_STATE_WALKING) ani = PARA_GOOMBA_ANI_WALKING;
		else ani = PARA_GOOMBA_ANI_FLY;
	}
	else if (state == PARA_GOOMBA_STATE_GOOMBA)
	{
		ani = PARA_GOOMBA_ANI_GOOMBA;
	}
	else if (state == PARA_GOOMBA_STATE_DIE)
	{
		ani = PARA_GOOMBA_ANI_DIE;
	}
	
	animation_set->at(ani)->Render(0, x, y);
	RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == PARA_GOOMBA_STATE_WALKING || state == PARA_GOOMBA_STATE_GOOMBA)
	{
		StartWalking();
		isOnGround = true;
		vx = -GOOMBA_WALKING_SPEED;
	}
	else if (state == PARA_GOOMBA_STATE_FLY)
	{
		vy = -0.15f;
		isOnGround = false;
		if (jumpingTimes == JUMPING_TIMES_BEFORE_HIGH_JUMP)
		{
			vy = -0.35f;
			jumpingTimes = 0;
			//SetState(PARA_GOOMBA_STATE_WALKING);
		}
		
	}

}