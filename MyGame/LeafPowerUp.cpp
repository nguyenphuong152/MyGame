#include "LeafPowerUp.h"
#include "Utils.h"
#include "Brick.h"

CLeafPowerUp::CLeafPowerUp(float x, float y)
{
	isEnable = true;
	start_y = y;
	SetPosition(x, y - 1);
	SetAnimation(LEAF_ANI);
}

void CLeafPowerUp::SetState(int state)
{
	CPowerUp::SetState(state);
	if (state == LEAF_STATE_GO_UP)
	{
		vy = -LEAF_DEFLECT_SPEED;
	}
}

void CLeafPowerUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CPowerUp::GetBoundingBox(l, t, r, b);
}

void CLeafPowerUp::Render()
{
	animation_set->at(POWER_UP_ANI)->Render(1, x, y);
}

void CLeafPowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CPowerUp::Update(dt, colObject);

	if (state==LEAF_STATE_GO_UP) vy += POWER_UP_GRAVITY / 3 * dt;

	if(vy>0)
	{
		vy = LEAF_DEFLECT_SPEED/5;
		vx = LEAF_VELOCITY_X * direction;
		if (changeDirection == 0)StartChangeDirection();
	}

	if (GetTickCount64() - changeDirection_start > FLOATING_TIME && changeDirection == 1)
	{
		changeDirection = 0;
		changeDirection_start = 0;
		direction = -direction;
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
			if (dynamic_cast<CBrick*>(e->obj))
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