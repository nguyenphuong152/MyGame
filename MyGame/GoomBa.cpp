#include "GoomBa.h"
#include "Utils.h"
#include "Box.h"
#include "Pipe.h"
#include "Brick.h"
#include "ParaGoomba.h"
#include "PowerUp.h"
#include "EffectPool.h"
#include "Effect.h"
#include "Ground.h"
#include "Grid.h"

CGoomBa::CGoomBa()
{
	ny = 1;
	SetState(GOOMBA_STATE_WALKING);
	SetLevel(GOOMBA_LEVEL_1);
}

void CGoomBa::DieWithDeflect(AttackedBy obj)
{
	if (GetLevel() == GOOMBA_LEVEL_2)
	{
		SetLevel(GOOMBA_LEVEL_1);
	}

	SetState(GOOMBA_STATE_DIE_WITH_DEFLECT);

	if(obj!=AttackedBy::KoopaShell)
	SetAttackedAnimation(obj, Points::NONE);
}


void CGoomBa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GOOMBA_BBOX_WIDTH;
	if (level == GOOMBA_LEVEL_1)
	{
		if (state == GOOMBA_STATE_DIE)
			b = y + GOOMBA_BBOX_HEIGHT_DIE;
		else
			b = y + GOOMBA_BBOX_HEIGHT;
	}
}

void CGoomBa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	
	vy += GOOMBA_GRAVITY * dt;

	if (GetTickCount64() - die_start > GOOMBA_DIE_TIME && die) {
		isEnable = false;
	}

	CEnemy::Update(dt, coObjects);


	if (state == GOOMBA_STATE_DIE_WITH_DEFLECT)
	{
		x += dx;
		y += dy;
	}

	HandleCollision(coEventsResult);
			
	ClearCoEvents();
	grid_->Move(this);
}

void CGoomBa::Render()
{
	int ani=-1;
	if (state == GOOMBA_STATE_WALKING || state==GOOMBA_STATE_DIE_WITH_DEFLECT)
	{
		ani = GOOMBA_ANI_WALKING;
	}
	else
	{
		ani = GOOMBA_ANI_DIE;
	}
	
	animation_set->at(ani)->Render(1,ny, x, y);
	//RenderBoundingBox();
}

void CGoomBa::HandleCollision(vector<LPCOLLISIONEVENT> coEventRe)
{
	//collision logic with other objects
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

		}
		else if (dynamic_cast<CBox*>(e->obj))
		{
			x += dx;
		}
	}
}

void CGoomBa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE;
		vx = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_DIE_WITH_DEFLECT:
		vx = 3*GOOMBA_WALKING_SPEED*nx;
		vy = -GOOMBA_DEFLECT_SPEED;
		ny = -1;
		break;
	}
}


