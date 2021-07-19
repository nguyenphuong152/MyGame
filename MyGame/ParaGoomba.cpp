#include "ParaGoomba.h"
#include "Utils.h"
#include "Brick.h"
#include "Ground.h"
#include "PowerUp.h"
#include "Grid.h"

CParaGoomba::CParaGoomba()
{
	nx = -1;
	ny = 1;
	SetLevel(GOOMBA_LEVEL_2);
	SetState(PARA_GOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{ 
	if (level == GOOMBA_LEVEL_2)
	{
		l = x;
		t = y;
		r = x + GOOMBA_BBOX_WIDTH;

		if (state == PARA_GOOMBA_STATE_WALKING)
		{
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING;
		}
		else {
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY;
		}
	}
	else {
		CGoomBa::GetBoundingBox(l, t, r, b);
	}
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (level == GOOMBA_LEVEL_2)
	{
		CEnemy::Update(dt, coObjects);
		vy += GOOMBA_GRAVITY * dt;

		if (walking == 1 && GetTickCount64() - walking_start > PARA_GOOMBA_WALKING_TIME)
		{
			walking = 0;
		}

		if (isOnGround && walking == 0)
		{
			if (jumpingTimes > JUMPING_TIMES_BEFORE_HIGH_JUMP)
			{
				SetState(PARA_GOOMBA_STATE_WALKING);
			}
			else
			{
				SetState(PARA_GOOMBA_STATE_FLY);
				jumpingTimes += 1;
			}
		}
			//collision logic with other objects
		HandleCollision(coEventsResult);
		ClearCoEvents();
		grid_->Move(this);
	}
	else {
		CGoomBa::Update(dt, coObjects);
	}
}

void CParaGoomba::Render()
{
	int ani = -1;
	if (level == GOOMBA_LEVEL_2)
	{
		if (state == PARA_GOOMBA_STATE_WALKING) ani = PARA_GOOMBA_ANI_WALKING;
		else ani = PARA_GOOMBA_ANI_FLY;
	}
	else if (level == GOOMBA_LEVEL_1)
	{
		if (state == GOOMBA_STATE_DIE)
		{
			ani = PARA_GOOMBA_ANI_DIE;
		}
		else
		{
			ani = PARA_GOOMBA_ANI_GOOMBA;
		}
	}
	
	animation_set->at(ani)->Render(nx,ny, x, y);
	//RenderBoundingBox();
}

void CParaGoomba::HandleCollision(vector<LPCOLLISIONEVENT> coEventRe)
{
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CPowerUp*>(e->obj) || dynamic_cast<CGround*>(e->obj))
		{
			if (e->nx != 0)
			{
				this->nx = -this->nx;
				vx = this->nx * GOOMBA_WALKING_SPEED;
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
}

void CParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	if (level == GOOMBA_LEVEL_2)
	{
		if (state == PARA_GOOMBA_STATE_WALKING)
		{
			StartWalking();
			isOnGround = true;
			jumpingTimes = 0;
			vx = nx * GOOMBA_WALKING_SPEED;
		}
		else if (state == PARA_GOOMBA_STATE_FLY)
		{
			isOnGround = false;
			if (jumpingTimes == JUMPING_TIMES_BEFORE_HIGH_JUMP)
			{
				vy = -PARA_GOOMBA_HIGH_JUMP_VELOCITY_Y;
			}
			else
			{
				vy = -PARA_GOOMBA_SHORT_JUMP_VELOCITY_Y;
			}

		}
	}
	else {
		CGoomBa::SetState(state);
	}

}
