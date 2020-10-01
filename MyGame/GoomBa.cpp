#include "GoomBa.h"
#include "Pipe.h"
#include "Box.h"
#include "Utils.h"

CGoomBa::CGoomBa()
{
	SetState(GOOMBA_STATE_WALKING);
}


void CGoomBa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		b = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		b = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomBa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isEnable) return;
	CGameObject::Update(dt, coObjects);
	
	if (x > POSITION_REACH_GROUND) {
		vx = -GOOMBA_WALKING_SPEED;
		x = POSITION_REACH_GROUND;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != GOOMBA_STATE_DIE)
	{
		CalcPotentialCollisions(coObjects, coEvents);
	}
	
	if (coEvents.size() == 0)
	{
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;

		if (state != GOOMBA_STATE_DIE)
		{
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}

		//day object ra mot khoang de k bi chong va cham
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//collision logic with other objects
		for (UINT i = 0;i < coEventsResult.size();i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			
			if (dynamic_cast<CPipe*>(e->obj)) 
			{
				if (e->nx != 0)
				{
					 SetState(GOOMBA_STATE_CHANGE_DIRECTION);
					 x += dx;
				}

			}
			else if (dynamic_cast<CBox*>(e->obj)) 
			{
				x += dx;
			}
		}
	}

	//DebugOut(L"[INFO]vy: %f \n", vy);

	for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];
}

void CGoomBa::Render()
{
	int ani;
	if (isEnable)
	{
		if (state == GOOMBA_STATE_WALKING || state == GOOMBA_STATE_CHANGE_DIRECTION)
		{
			ani = GOOMBA_ANI_WALKING;
		}
		
	}
	else {
		if (GetTickCount() - die_start < GOOMBA_DIE_TIME)
		{
			if (state == GOOMBA_STATE_DIE)
			{
				ani = GOOMBA_ANI_DIE;
			}
		}
		else return;
	}
	
	//hardcode
	animation_set->at(ani)->Render(1, x, y);
}

void CGoomBa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	case GOOMBA_STATE_CHANGE_DIRECTION:
		vx = GOOMBA_WALKING_SPEED;
		break;
	}
}
