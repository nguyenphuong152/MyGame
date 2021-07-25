#include "PowerUp.h"
#include "Mario.h"
#include "Brick.h"
#include "Ground.h"
#include "Camera.h"
#include "Utils.h"
#include "Box.h"
#include "Game.h"

CPowerUp::CPowerUp(float x,float  y)
{
	changeDirection_start = 0;
	isEnable = true;
	start_y = y;
	powerup_type = PowerUpType::none;
	SetPosition(x+0.1f,y);
	player = CGame::GetInstance()->GetPlayer();
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
			float nx = 0, ny;
			FilterCollision(coEvents, coEventsResult,nx,ny);

			//collision logic with other objects
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];
				if (dynamic_cast<CBrick*>(e->obj) && GetPowerUpType() == PowerUpType::super_leaf)
				{
					x += dx;
					y += dy;
				}
				else if (dynamic_cast<CGround*>(e->obj))
				{
					if (e->nx != 0 && GetPowerUpType() == PowerUpType::super_mushroom){
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
				else if(dynamic_cast<CBox*>(e->obj)) {
					if (e->nx != 0)
					{
						vx = this->nx * MUSHROOM_VELOCITY_X;
						x += dx;
					}
				}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
    
}

void CPowerUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y+1;
	r = x + POWER_UP_BBOX_WIDTH;
	b = y + POWER_UP_BBOX_WIDTH;

	if (isActive)
	{
		b = y + POWER_UP_BBOX_WIDTH + 9;
	}
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
		animation_set->at(POWER_UP_ANI)->Render(1,1, x, y);
		RenderBoundingBox();
	}
}


void CPowerUp::DefinePowerUpType()
{
	int level = player->GetLevel();

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
		nx = -player->nx;
		vx = MUSHROOM_VELOCITY_X * nx;
	}
}

void CPowerUp::SetStateForSuperLeaf()
{
	if (state == POWERUP_STATE_GO_UP)
	{
		vy = -LEAF_DEFLECT_SPEED;
	}
	StartMoving();
}

void CPowerUp::HandleUpdateSuperLeaf()
{
	if (state == POWERUP_STATE_GO_UP) vy += POWER_UP_GRAVITY / 3 * dt;

	if (vy > 0)
	{
		vy = LEAF_DEFLECT_SPEED / 6;
		vx = LEAF_VELOCITY_X * direction;
		if (changeDirection == 0)  StartChangeDirection();
	}

	if (GetTickCount64() - changeDirection_start > POWER_UP_FLOATING_TIME && changeDirection == 1)
	{
		changeDirection = 0;
		changeDirection_start = 0;
		direction = -direction;
	}

	if (GetTickCount64() - moving_start > POWER_UP_ALIVE_TIME && moving == 1)
	{
		isEnable = false;
	}

}

void CPowerUp::HandleUpdateSuperMushroom()
{
	if (state == POWERUP_STATE_WALKING) vy += POWER_UP_GRAVITY * dt;

	if (y <= start_y - BRICK_BBOX_WIDTH-2 )
	{
		SetState(POWERUP_STATE_WALKING);
	}
}