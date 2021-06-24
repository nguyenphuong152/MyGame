#include "RedVenusFireTrap.h"
#include "RedVenusFireTrap.h"
#include "Ground.h"
#include "FireBall.h"
#include "FireBallPool.h"
#include "EffectPool.h"


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

	if (state == VENUS_STATE_GO_UP || state == VENUS_STATE_GO_DOWN)
	{
		if (vy <= 0) vy = VENUS_VELOCITY_Y;
		else vy = -VENUS_VELOCITY_Y;
	}

}

void CRedVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	CheckDirectionForRender(POSITION_PIPE_X);
	//go up and start shooting then change state go down when it go over the pipe
	HandleShooting(POSITION_PIPE_Y, VENUS_BBOX_HEIGHT);

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
				if (e->ny < 0)
				{
					if(player->y> POSITION_PIPE_Y-45)
						SetState(VENUS_STATE_GO_DOWN);
					else SetState(VENUS_STATE_GO_UP);
				}

			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}


void CRedVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + VENUS_BBOX_WIDTH;
	b = y + VENUS_BBOX_HEIGHT;
}

void CRedVenusFireTrap::CheckDirection()
{
	float mario_y = player->y;
	if (player->GetLevel() != MARIO_LEVEL_SMALL)
	{
		mario_y += MARIO_BIG_BBOX_HEIGHT-MARIO_SMALL_BBOX_HEIGHT;
	}

	if (mario_y> POSITION_PIPE_Y-50)
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
		DWORD now = GetTickCount();
		if (now - startShooting > TIME_SHOOTING)
		{
			isShooting = false;
			startShooting = -1;
			if (player->y > position_pipe - 45)
			{
				SetState(VENUS_STATE_GO_DOWN);
			}
			else
			{
				SetState(VENUS_STATE_GO_UP);
			}
		}
	}
}
