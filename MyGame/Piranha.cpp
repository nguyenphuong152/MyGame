#include "Piranha.h"
#include "Ground.h"
#include "Utils.h"
#include "EffectPool.h"

CPiranha::CPiranha()
{
	isEnable = true;
	SetState(PIRANHA_STATE_ACTIVE);
	vy = PIRANHA_VELOCITY_Y;
}

void CPiranha::Render()
{
	int ani = PIRANHA_ANI_ACTIVE;
	animation_set->at(ani)->Render(0, x, y);
}


void CPiranha::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIRANHA_BBOX_WIDTH;
	b = y + PIRANHA_BBOX_HEIGHT;
}


void CPiranha::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (y < PIPE_POSITION_Y && active == 0) StartActive();

	if (GetTickCount64() - active_start > ACTIVE_TIME && active)
	{
		ResetActive();
		vy = PIRANHA_VELOCITY_Y;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;


		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//day object ra mot khoang de k bi chong va cham
		y += min_ty * dy + ny * 0.4f;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0 &&y >PIPE_POSITION_Y)
				{
					vy = -PIRANHA_VELOCITY_Y;
				}
				else
				{
					vy = PIRANHA_VELOCITY_Y;
					y += dy;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CPiranha::StartActive()
{
	active_start = GetTickCount64();
	active = 1;
	vy = 0;
}

void CPiranha::ResetActive()
{
	active = 0;
	active_start = 0;
}

void CPiranha::SetAttackedAnimation()
{
	CEffect* effect = CEffectPool::GetInstance()->Create();
	if (effect != NULL)
	{
		effect->SetEffect(EffectName::attack_by_tail, this);
	}
}