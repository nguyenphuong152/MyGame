#include "GoomBa.h"
#include "Utils.h"
#include "Box.h"
#include "Pipe.h"
#include "Brick.h"
#include "ParaGoomba.h"
#include "PowerUp.h"
#include "EffectPool.h"
#include "Effect.h"

CGoomBa::CGoomBa()
{
	ny = 1;
	SetState(GOOMBA_STATE_WALKING);
	SetLevel(GOOMBA_LEVEL_1);
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
	CEnemy::Update(dt, coObjects);
	
	vy += GOOMBA_GRAVITY * dt;

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
		if (state == GOOMBA_STATE_DIE_WITH_DEFLECT)
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

				if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CPowerUp*>(e->obj))
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

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
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
		vx = 4*GOOMBA_WALKING_SPEED*nx;
		SetAttackedAnimation(AttackedBy::Tail,Points::NONE);
		break;
	}
}

