#include "GreenVenusFireTrap.h"
#include "Ground.h"
#include "FireBall.h"
#include "FireBallPool.h"


CGreenVenusFireTrap::CGreenVenusFireTrap()
{
	SetAnimation();
	isEnable = true;
	startShooting = -1;
	isShooting = false;
	isShootingUp = false;
	SetState(VENUS_STATE_GO_UP);
}

void CGreenVenusFireTrap::Render()
{
	CRedVenusFireTrap::Render();
}

void CGreenVenusFireTrap::SetState(int state)
{
	CRedVenusFireTrap::SetState(state);
}

void CGreenVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (CMario::GetInstance()->x < POSITION_PIPE_X)  nx = -1;
	else nx = 1;

	//go up and start shooting then change state go down when it go over the pipe
	if (!isShooting)
	{
		if (y < POSITION_PIPE_Y - GREEN_VENUS_BBOX_HEIGHT && vy <= 0)
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
			if (CMario::GetInstance()->y > POSITION_PIPE_Y - 45)
			{
				SetState(VENUS_STATE_GO_DOWN);
			}
			else
			{
				SetState(VENUS_STATE_GO_UP);
			}
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
		y += min_ty * dy + ny * 0.4f;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
				{
					if (CMario::GetInstance()->y > POSITION_PIPE_Y - 45)
						SetState(VENUS_STATE_GO_DOWN);
					else SetState(VENUS_STATE_GO_UP);
				}

			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}


void CGreenVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CRedVenusFireTrap::GetBoundingBox(l, t, r, b);
}

void CGreenVenusFireTrap::CheckDirection()
{
	CRedVenusFireTrap::CheckDirection();
}

void CGreenVenusFireTrap::StartShooting()
{
	CRedVenusFireTrap::StartShooting();
}

void CGreenVenusFireTrap::SetAnimation()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(GREEN_VENUS_FIRETRAP_ANI);
	SetAnimationSet(ani_set);
}
