#include "Piranha.h"
#include "Ground.h"
#include "Utils.h"
#include "EffectPool.h"
#include "Grid.h"

CPiranha::CPiranha()
{
	SetState(PIRANHA_STATE_GO_UP);
}

void CPiranha::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == PIRANHA_STATE_GO_UP)
	{
		vy = -PIRANHA_VELOCITY_Y;
		StartChangeState();
	}
	else if (state == PIRANHA_STATE_GO_DOWN)
	{
		vy = PIRANHA_VELOCITY_Y;
		StartChangeState();
	}

}

void CPiranha::Render()
{
	int ani = PIRANHA_ANI_ACTIVE;
	animation_set->at(ani)->Render(1,1, x, y);
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
	if (GetTickCount64() - changeState_start > ACTIVE_TIME && changeState == 1)
	{
		ResetChangeState();
		SetState(PIRANHA_STATE_GO_DOWN);
	}

	CGameObject::Update(dt);

	HandleCollision(coObjects);

	grid_->Move(this);
}

void CPiranha::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
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
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny != 0)
				{
					if (y > PIRANHA_PIPE_POSITION_Y)
					{
						if (player->x<(x - MARIO_BIG_BBOX_WIDTH*2) || player->x>(x + MARIO_BIG_BBOX_WIDTH * 2))
						  SetState(PIRANHA_STATE_GO_UP);
					}
					else {
						SetState(PIRANHA_STATE_GO_DOWN);
					}
					if (player->x<(x - MARIO_BIG_BBOX_WIDTH*2) || player->x>(x + MARIO_BIG_BBOX_WIDTH * 2))
					   y += dy;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

