#include "RedVenusFireTrap.h"
#include "RedVenusFireTrap.h"
#include "Ground.h"
#include "FireBall.h"
#include "FireBallPool.h"
#include "EffectPool.h"
#include "Grid.h"


CRedVenusFireTrap ::CRedVenusFireTrap()
{
	startShooting = -1;
	isShooting = false;
	isShootingUp = false;
	SetState(VENUS_STATE_GO_UP);
}

void CRedVenusFireTrap::Render()
{
	int ani = -1;
	if (state == VENUS_STATE_GO_UP)
	{
		ani = VENUS_ANI_GO_UP;
	}
	else if (state == VENUS_STATE_GO_DOWN)
	{
		ani = VENUS_ANI_GO_DOWN;
	}
	else if (state == VENUS_STATE_SHOOT_UP)
	{
		ani = VENUS_ANI_SHOOT_UP;
	}
	else if (state == VENUS_STATE_SHOOT_DOWN)
	{
		ani = VENUS_ANI_SHOOT_DOWN;
	}

	
		animation_set->at(ani)->Render(nx,1, x, y);
}

void CRedVenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);

	if (state == VENUS_STATE_GO_UP)
	{
	   vy = -VENUS_VELOCITY_Y;
	   StartChangeState();
	}
	else if (state == VENUS_STATE_GO_DOWN)
	{
		vy = VENUS_VELOCITY_Y;
		StartChangeState();
	}

}

void CRedVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CheckDirectionForRender(POSITION_PIPE_X);

	//go up and start shooting then change state go down when it go over the pipe
	HandleShooting(POSITION_PIPE_Y, VENUS_BBOX_HEIGHT);

	if (GetTickCount64() - changeState_start > RED_VENUS_MOVING_TIME && changeState == 1)
	{
		ResetChangeState();
		SetState(VENUS_STATE_GO_DOWN);
	}

	CGameObject::Update(dt);

	
	HandleCollision(coObjects);
	grid_->Move(this);
}


void CRedVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + VENUS_BBOX_WIDTH;
	b = y + VENUS_BBOX_HEIGHT;
}

void CRedVenusFireTrap::HandleCollision(vector<LPGAMEOBJECT>* coEventRe)
{
	//collision logic with other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coEventRe, coEvents);

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
					if (y > POSITION_PIPE_Y)
					{
						SetState(VENUS_STATE_GO_UP);
					}
					else {
						SetState(VENUS_STATE_GO_DOWN);
					}
					y += dy;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CRedVenusFireTrap::CheckDirection()
{
	float mario_y = player->y;
	if (player->GetLevel() != MARIO_LEVEL_SMALL)
	{
		mario_y += MARIO_BIG_BBOX_HEIGHT-MARIO_SMALL_BBOX_HEIGHT;
	}

	if (mario_y> POSITION_PIPE_Y-100)
	{
		state = VENUS_STATE_SHOOT_DOWN;
	}
	else
	{
		state = VENUS_STATE_SHOOT_UP;
		isShootingUp = true;
	}
}

void CRedVenusFireTrap::StartShooting()
{
	startShooting = GetTickCount64(); 
	isShooting = true;

	vy = 0;

	CFireball* fireball = CFireBallPool::GetInstance()->Create();
	fireball->AllocateFireballToVenus(nx,x,y,isShootingUp);
	if (isShootingUp) isShootingUp = false;
}

void CRedVenusFireTrap::CheckDirectionForRender(int position_pipe)
{
	if (player->x < position_pipe)  nx = -1;
	else nx = 1;
}

void CRedVenusFireTrap::HandleShooting(int position_pipe, int bbox_height)
{
	if (!isShooting)
	{
		if (y < position_pipe - bbox_height + 5 && vy <= 0)
		{
			CheckDirection();
			StartShooting();
		}
	}
	else {
		if (GetTickCount64() - startShooting > TIME_SHOOTING)
		{
			isShootingUp = false;
			isShooting = false;

			startShooting = -1;	
		}
	}
}
