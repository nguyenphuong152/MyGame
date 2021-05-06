#include "MushroomPowerUp.h"
#include "Brick.h"
#include "Utils.h"
#include "Boundary.h"
#include "Ground.h"
#include "Mario.h"

CMushroomPowerUp::CMushroomPowerUp(float x, float y, MushroomType type)
{
	isEnable = true;
	start_y = y;
	SetPosition(x, y - 1);
	if(type==MushroomType::red_mushroom) 
		SetAnimation(RED_MUSHROOM_ANI);
	else SetAnimation(GREEN_MUSHROOM_ANI);
}

void CMushroomPowerUp::SetState(int state)
{
	CPowerUp::SetState(state);
	if (state == MUSHROOM_STATE_GO_UP)
	{
		vy = -MUSHROOM_VELOCITY_Y;
	}
	else
	{
		nx = -CMario::GetInstance()->nx;
		vx = MUSHROOM_VELOCITY_X * nx;
	}
}

void CMushroomPowerUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CPowerUp::GetBoundingBox(l, t, r, b);
}

void CMushroomPowerUp::Render()
{
	animation_set->at(POWER_UP_ANI)->Render(1, x, y);
}

void CMushroomPowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CPowerUp::Update(dt, colObject);

	if (state == MUSHROOM_STATE_WALKING) vy += POWER_UP_GRAVITY * dt;

	if (y <= start_y - BRICK_BBOX_HEIGHT-1)
	{
		SetState(MUSHROOM_STATE_WALKING);
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

			if (dynamic_cast<CBoundary*>(e->obj))
			{
				if (e->nx != 0)
				{
					isEnable = false;
				}
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->nx != 0)
				{
					this->nx = -this->nx;
					vx = this->nx * MUSHROOM_VELOCITY_X;
				}
			}
			else {
				x += dx;
				vx = this->nx * MUSHROOM_VELOCITY_X;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
    
}