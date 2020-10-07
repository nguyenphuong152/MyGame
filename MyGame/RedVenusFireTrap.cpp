#include "RedVenusFireTrap.h"
#include "Ground.h"


CRedVenusFireTrap ::CRedVenusFireTrap(CMario *player)
{
	isEnable = true;
	this->player = player;
	startShooting = -1;
	isShooting = false;
	isGoingUp = true;
	hasFireBall = false;
	SetState(RED_VENUS_STATE_GO_DOWN);
}

void CRedVenusFireTrap::Render()
{
	int ani=-1;
	if (state == RED_VENUS_STATE_GO_UP)
	{
		ani = RED_VENUS_ANI_GO_UP;
	}
	else if (state == RED_VENUS_STATE_GO_DOWN)
	{
		ani = RED_VENUS_ANI_GO_DOWN;
	}
	else if (state == RED_VENUS_STATE_SHOOT_UP)
	{
		ani = RED_VENUS_ANI_SHOOT_UP;
	}
	else if (state == RED_VENUS_STATE_SHOOT_DOWN)
	{
		ani = RED_VENUS_ANI_SHOOT_DOWN;
	}
	if (player->x < POSITION_PIPE)
	animation_set->at(ani)->Render(-1, x, y);
	else animation_set->at(ani)->Render(1, x, y);

}

void CRedVenusFireTrap::SetState(int state)
{
	CGameObject::SetState(state);
	
	if (state == RED_VENUS_STATE_GO_UP)
	{
		vy = -RED_VENUS_VELOCITY_Y;
		if (!isGoingUp) vy = RED_VENUS_VELOCITY_Y;
	}
	else if (state == RED_VENUS_STATE_GO_DOWN)
	{
		vy = RED_VENUS_VELOCITY_Y;
		if (isGoingUp) vy = -RED_VENUS_VELOCITY_Y;
	}
}

void CRedVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (isShooting)
	{
		//DebugOut(L"shooting: %d \n",startShooting);
		DWORD now = GetTickCount();
		//DebugOut(L"now: %d \n", now);
		if (now - startShooting >= TIME_SHOOTING)
		{
			isGoingUp = false;
			isShooting = false;
			hasFireBall = false;
			if (player->y > POSITION_MIDDLE_MOVING)
			{
				SetState(RED_VENUS_STATE_GO_DOWN);
			}
			else 
			{
				SetState(RED_VENUS_STATE_GO_UP);
			}
		}
	}

	CheckDirection();

	if (isGoingUp)
	{
		if (y < POSITION_MOVING && !isShooting)
		{
			if (player->y > POSITION_MIDDLE_SHOOTING)
			{
				SetState(RED_VENUS_STATE_SHOOT_DOWN);
				//if (isGoingUp) SetState(RED_VENUS_STATE_GO_DOWN);
			}
			else
			{
				SetState(RED_VENUS_STATE_SHOOT_UP);
			}
			StartShooting();
		}
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
		y += dy;

		//collision logic with other objects
		for (UINT i = 0;i < coEventsResult.size();i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
				{
					//xet is going up truoc khi setstate de no biet di len hay di xuong
					isGoingUp = true;
					if (state == RED_VENUS_STATE_GO_UP) {
						SetState(RED_VENUS_STATE_GO_UP);
					}
					else if (state == RED_VENUS_STATE_GO_DOWN) {
						SetState(RED_VENUS_STATE_GO_DOWN);
					}
				}

			}
		}
	}

	//DebugOut(L"[INFO]vy: %f \n", vy);

	for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];
}

void CRedVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + RED_VENUS_BBOX_WIDTH;
	b = y + RED_VENUS_BBOX_HEIGHT;
}

void CRedVenusFireTrap::CheckDirection()
{
	float mario_y = player->y;
	if (player->level == MARIO_LEVEL_BIG)
	{
		mario_y += MARIO_BIG_BBOX_HEIGHT-MARIO_SMALL_BBOX_HEIGHT;
	}
	if (mario_y > POSITION_MIDDLE_MOVING)
	{
		if (!isShooting)
		{
			state = RED_VENUS_STATE_GO_DOWN;
		}
		else 
		{
			if(mario_y > POSITION_MIDDLE_SHOOTING)
			state = RED_VENUS_STATE_SHOOT_DOWN;
			else state = RED_VENUS_STATE_SHOOT_UP;
		}
	}
	else
	{
		if (!isShooting)
		{
			state = RED_VENUS_STATE_GO_UP;
		}
		else
		{
			if(mario_y < POSITION_MIDDLE_SHOOTING)
			state = RED_VENUS_STATE_SHOOT_UP;
			else
				state = RED_VENUS_STATE_SHOOT_DOWN;

		}
	}
}

void CRedVenusFireTrap::StartShooting()
{
	startShooting = GetTickCount(); 
	isShooting = true;
	vy = 0;
}