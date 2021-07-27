#include "BoomerangBrother.h"
#include "ObjectBoundary.h"
#include "Ground.h"
#include "Boomerang.h"
#include "BoomerangPool.h"
#include "Game.h"
#include "Grid.h"

CBoomerangBrother::CBoomerangBrother()
{
	nx = direction = -1;
	ny = 1;

	isHitted = true;
	
	isOnGround = false;
	isWalking = false;
	_startWalking = 0;
    _startThrowing = 0;
	disableThrowing = false;
	countingTime = 0;

	StartThrowing();
	SetState(BOOMERANGBROTHER_STATE_WALKING);
}

void CBoomerangBrother::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + BOOMERANGBROTHER_BBOX_WIDTH;
	t = y;
	b = y + BOOMERANGBROTHER_BBOX_HEIGHT;
}

void CBoomerangBrother::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);
	vy += BOOMERANGBROTHER_GRAVITY * dt;

	//check dieu kien nhay
	BoomerangBrotherJump();

	if (GetTickCount64() - die_start > DIETIME && die) isEnable = false;

	//doi huong tuy theo mario
	CheckDirection();

	//check dieu kien quang bmr
	BoomerangBrotherThrowBoomerang();
	
	if (state == BOOMERANGBROTHER_STATE_DIE) {
		x += dx;
		y += dy;
	}
	//collision logic with other objects
	
	HandleCollision(coObjects);
	grid_->Move(this);
}

void CBoomerangBrother::Render()
{
	int ani = BOOMERANGBROTHER_ANI_WALKING;
	
	if (state == BOOMERANGBROTHER_STATE_THROWING) {
		//DebugOut(L"voooooooooooo %d \n", countingTime);
		ani = BOOMERANGBROTHER_ANI_THROW_ARMY;
	}

	//change direction for koopas
	animation_set->at(ani)->Render(nx, ny, x, y);
	RenderBoundingBox();
}

void CBoomerangBrother::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

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
				if (e->ny < 0)
				{
					isOnGround = true;
				}
			}
			else if (dynamic_cast<CObjectBoundary*>(e->obj))
			{
				if (e->nx != 0)
				{
					direction = -direction;
					vx = BOOMERANGBROTHER_WALKING_SPEED * direction;
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerangBrother::BoomerangBrotherJump()
{
	if (isOnGround && GetTickCount64() - _startWalking > WALKING_TIME && isWalking)
		SetState(BOOMERANGBROTHER_STATE_JUMPING);
	if(isOnGround && !isWalking)
	    SetState(BOOMERANGBROTHER_STATE_WALKING);
}

void CBoomerangBrother::CheckDirection()
{
	CMario* player = CGame::GetInstance()->GetPlayer();
	if (player->x > x)
	{
		nx = 1;
	}
	else {
		nx = -1;
	}
}

void CBoomerangBrother::BoomerangBrotherThrowBoomerang()
{
	if (GetTickCount64() - _startThrowing > DISABLE_THROWING_TIME && disableThrowing == true 
		&& isHitted == true && countingTime < THROWING_TIMES)
	{
		SetState(BOOMERANGBROTHER_STATE_THROWING);
		countingTime++;

	}
	else if (countingTime == THROWING_TIMES) {
		ResetThrowing();
		StartThrowing();
		SetState(BOOMERANGBROTHER_STATE_WALKING);
	}

}

void CBoomerangBrother::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == BOOMERANGBROTHER_STATE_WALKING)
	{
		vx = BOOMERANGBROTHER_WALKING_SPEED * direction;
		StartWalking();
	}
	else if (state == BOOMERANGBROTHER_STATE_JUMPING) {
		ResetWalking();
		vy = -BOOMERANGBROTHER_DEFLECT_SPEED;
		isOnGround = false;
	}
	else if (state == BOOMERANGBROTHER_STATE_THROWING)
	{
		CBoomerang* bmr = CBoomerangPool::GetInstance()->Create();
		if (bmr != NULL)
		{
			bmr->StartThrowing(this);
			isHitted = false;
		}
	}
	else {
		vx = 0;
		vy = -BOOMERANGBROTHER_DEFLECT_SPEED;
		ny = -1;
		StartDie();
	}

}
