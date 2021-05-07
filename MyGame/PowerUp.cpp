#include "PowerUp.h"
#include "Mario.h"
#include "Brick.h"
#include "Ground.h"
#include "Camera.h"

CPowerUp::CPowerUp(float x,float  y)
{
	changeDirection_start = 0;
	isEnable = true;
	start_y = y;
	powerup_type = PowerUpType::none;
	SetPosition(x, y - 1);
}

void CPowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{

	CGameObject::Update(dt, colObject);

	if (isActive)
	{

		if (GetPowerUpType() == PowerUpType::super_leaf)
			HandleUpdateSuperLeaf();
		else
			HandleUpdateSuperMushroom();

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
				if (dynamic_cast<CBrick*>(e->obj) && GetPowerUpType() == PowerUpType::super_leaf)
				{
					if (e->ny < 0)
					{
						isEnable = false;
					}
				}
				else if (dynamic_cast<CGround*>(e->obj) && GetPowerUpType() == PowerUpType::super_mushroom)
				{
					if (e->nx != 0)
					{
						this->nx = -this->nx;
						vx = this->nx * MUSHROOM_VELOCITY_X;
					}
				}
				else if (dynamic_cast<CCamera*>(e->obj))
				{
					if (e->nx != 0 || e->ny != 0)
					{
						isEnable = false;
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
    
}

void CPowerUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + POWER_UP_BBOX_WIDTH;
	b = y + POWER_UP_BBOX_WIDTH;
}

void CPowerUp::SetState(int state)
{
	CGameObject::SetState(state);
	if (GetPowerUpType() == PowerUpType::super_leaf)
		SetStateForSuperLeaf();
	else SetStateForSuperMushroom();
}

void CPowerUp::Render()
{
	if (GetPowerUpType() != PowerUpType::none)
	{
		animation_set->at(POWER_UP_ANI)->Render(1, x, y);
	}
}


void CPowerUp::DefinePowerUpType()
{
	int level = CMario::GetInstance()->level;

	ActivatePower();

	if (level == MARIO_LEVEL_SMALL)
	{
		SetPowerUpType(PowerUpType::super_mushroom);
		SetAnimation(SUPER_MUSHROOM_ANI);
	}
	else
	{
		SetPowerUpType(PowerUpType::super_leaf);
		SetAnimation(SUPER_LEAF_ANI);
	}
}

void CPowerUp::SetStateForSuperMushroom()
{
	if (state == POWERUP_STATE_GO_UP)
	{
		vy = -MUSHROOM_VELOCITY_Y;
	}
	else
	{
		nx = -CMario::GetInstance()->nx;
		vx = MUSHROOM_VELOCITY_X * nx;
	}
}

void CPowerUp::SetStateForSuperLeaf()
{
	if (state == POWERUP_STATE_GO_UP)
	{
		vy = -LEAF_DEFLECT_SPEED;
	}
}

void CPowerUp::HandleUpdateSuperLeaf()
{
	if (state == POWERUP_STATE_GO_UP) vy += POWER_UP_GRAVITY / 3 * dt;

	if (vy > 0)
	{
		vy = LEAF_DEFLECT_SPEED / 5;
		vx = LEAF_VELOCITY_X * direction;
		if (changeDirection == 0)  StartChangeDirection();
	}

	if (GetTickCount64() - changeDirection_start > FLOATING_TIME && changeDirection == 1)
	{
		changeDirection = 0;
		changeDirection_start = 0;
		direction = -direction;
	}

}

void CPowerUp::HandleUpdateSuperMushroom()
{
	if (state == POWERUP_STATE_WALKING) vy += POWER_UP_GRAVITY * dt;

	if (y <= start_y - BRICK_BBOX_HEIGHT-1 )
	{
		SetState(POWERUP_STATE_WALKING);
	}
}