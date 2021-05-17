#include "One-upMushroom.h"
#include "PowerUp.h"
#include "Mario.h"
#include "Ground.h"
#include "Camera.h"
#include "Brick.h"
#include "Utils.h"

COneUpMushroom::COneUpMushroom(float x, float y)
{
	isEnable = true;
	start_y = y;
	SetPosition(x, y - 1);
}

void COneUpMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == ONE_UP_MUSHROOM_STATE_GO_UP)
	{
		vy = -MUSHROOM_VELOCITY_Y;
	}
	else
	{
		nx = -CMario::GetInstance()->nx;
		vx = MUSHROOM_VELOCITY_X * nx;
	}
}

void COneUpMushroom::Render()
{
	animation_set->at(ONE_UP_MUSHROOM_ANI)->Render(1,1, x, y);
}

void COneUpMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + POWER_UP_BBOX_WIDTH;
	b = y + POWER_UP_BBOX_WIDTH;
}

void COneUpMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{

	CGameObject::Update(dt, colObject);

	if (state == ONE_UP_MUSHROOM_STATE_WALKING) vy += POWER_UP_GRAVITY * dt;

	if (y <= start_y - BRICK_BBOX_HEIGHT - 1)
	{
		SetState(ONE_UP_MUSHROOM_STATE_WALKING);
	}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(colObject, coEvents);

		//if no collision occured, proceed normally
		if (coEvents.size() == 0)
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
				if (dynamic_cast<CGround*>(e->obj))
				{
					if (e->nx != 0)
					{
						this->nx = -this->nx;
						vx = this->nx * MUSHROOM_VELOCITY_X;
					}
				}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}