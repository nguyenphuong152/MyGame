#include "Coin.h"
#include "Utils.h"
#include "Brick.h"

CCoin::CCoin()
{
	isEnable = true;
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == COIN_STATE_JUMPING)
	{
		vy = -COIN_DEFLECT_SPEED;
	}
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (state == COIN_STATE_JUMPING) vy += COIN_GRAVITY * dt;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	//if no collision occured, proceed normally
	if (coEvents.size() == 0 )
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj) )
			{
				if (e->ny < 0)
				{
					isEnable = false;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CCoin::Render()
{
	int ani = -1;
	if (state == COIN_STATE_JUMPING)
		ani = COIN_ANI_JUMPING;
	else
		ani = COIN_ANI_IDLE;
	animation_set->at(ani)->Render(1,x,y);
	//RenderBoundingBox();
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}