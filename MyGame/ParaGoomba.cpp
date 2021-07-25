#include "ParaGoomba.h"
#include "Utils.h"
#include "Brick.h"
#include "Ground.h"
#include "PowerUp.h"
#include "Grid.h"

CParaGoomba::CParaGoomba()
{
	jumpingTimes = 0;
	nx = -1;
	ny = 1;
	SetLevel(GOOMBA_LEVEL_2);
	SetState(GOOMBA_STATE_WALKING);
}

void CParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{ 
	l = x;
	t = y;
	r = x + GOOMBA_BBOX_WIDTH;

	if (level == GOOMBA_LEVEL_2)
	{
		if (state == PARA_GOOMBA_STATE_FLY)
		{
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY;
		}
		else {
			b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING;
		}
	}
	else if (state == GOOMBA_STATE_DIE)
	{
		b = y + GOOMBA_BBOX_HEIGHT_DIE;
	}
	else b = y + PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING;
	
}

void CParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGoomBa::Update(dt,coObjects);

	if (level == GOOMBA_LEVEL_2)
	{
		if (walking == 1 && GetTickCount64() - walking_start > PARA_GOOMBA_WALKING_TIME)
		{
			walking = 0;
		}

		if (isOnGround && walking == 0)
		{
			if (jumpingTimes > JUMPING_TIMES_BEFORE_HIGH_JUMP)
			{
				jumpingTimes = 0;
				SetState(GOOMBA_STATE_WALKING);
			}
			else
			{
				SetState(PARA_GOOMBA_STATE_FLY);
			}
		}
	}
}

void CParaGoomba::Render()
{
	int ani = -1;

	if (level == GOOMBA_LEVEL_2)
	{
		if (state == GOOMBA_STATE_WALKING) ani = PARA_GOOMBA_ANI_WALKING;
		else if(state == PARA_GOOMBA_STATE_FLY) ani = PARA_GOOMBA_ANI_FLY;
	}
	else if (state == GOOMBA_STATE_WALKING || state == GOOMBA_STATE_DIE_WITH_DEFLECT) ani = PARA_GOOMBA_ANI_GOOMBA;
	else ani = PARA_GOOMBA_ANI_DIE;
	
	animation_set->at(ani)->Render(nx,ny, x, y);
	//RenderBoundingBox();
}

void CParaGoomba::SetState(int state)
{
    CGoomBa::SetState(state);
	if (state == GOOMBA_STATE_WALKING)
	{
		StartWalking();
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
		jumpingTimes++;
	}
}
