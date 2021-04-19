#include "Koopas.h"
#include "Utils.h"
#include "MarioStateIdle.h"
#include "Mario.h"
#include "Boundary.h"
#include "Box.h"
#include "ObjectBoundary.h"
#include "Ground.h"
#include "Brick.h"
#include "Pipe.h"
#include "Camera.h"

CKoopas::CKoopas()
{
	isEnable = true;
	this->player = CMario::GetInstance();
	nx = 1;
	SetAnimation();
	SetState(KOOPA_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + KOOPA_BBOX_WIDTH;

	if (state != KOOPA_STATE_WALKING)
	{
		t = y;
		b = y + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		t = y ;
		b = y + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt,coObjects);

	//die ->recover
	if (GetTickCount64() - _dieStart > KOOPA_DIE_TIME && die) {
		SetState(KOOPA_STATE_RECOVER);
	} 
	//recover->live
	if (GetTickCount64() - _recoverStart > KOOPA_RECOVER_TIME && recover) {
		//xet lai vi tri k thoi rua se bi roi xuong
		y -= KOOPA_BBOX_HEIGHT-KOOPA_BBOX_HEIGHT_DIE;
		SetState(KOOPA_STATE_WALKING);
	}

	if (isHolded)
	{
		if (player->isKicking)
		{
			SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
			isHolded = false;
		}
		else {
			UpdateShellPosition();
		}
	}
	else 
	{
		vy += KOOPA_GRAVITY * dt;
	}

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
		
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0, rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//day object ra mot khoang de k bi chong va cham
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CObjectBoundary*>(e->obj))
			{
				if (e->nx != 0) {
					this->nx = -this->nx;
					if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						vx = KOOPA_SHELL_VELOCITY_X * this->nx;
						x += dx;
					}
					else
						vx = KOOPA_WALKING_SPEED * this->nx;
					
				}
			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
						vx = KOOPA_SHELL_VELOCITY_X*this->nx;
					else
						vx = KOOPA_WALKING_SPEED*this->nx;
					x += dx;
				}
			}
			else if (dynamic_cast<CGround*>(e->obj)|| dynamic_cast<CBrick*>(e->obj)|| dynamic_cast<CPipe*>(e->obj))
			{
				if ( e->nx != 0)
				{
					if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						this->nx = -this->nx;
						vx = KOOPA_SHELL_VELOCITY_X * this->nx;
					}
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

}

void CKoopas::Render()
{
	int ani = KOOPA_ANI_WALKING;
	if (state == KOOPA_STATE_DIE)
		ani = KOOPA_ANI_DIE;
	else if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
		ani = KOOPA_ANI_DIE_WITH_VELOCITY;
	else if (state == KOOPA_STATE_RECOVER)
		ani = KOOPA_ANI_RECOVER;

	//change direction for koopas
	animation_set->at(ani)->Render(nx, x, y);
}


void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		y += KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE - 10 ;
		vx = 0;
		break;
	case KOOPA_STATE_WALKING:
		if (recover && _recoverStart != 0) {
			recover = 0;
			_recoverStart = 0;
		}
		vx = nx*KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DIE_WITH_VELOCITY:
		if (player->nx > 0)
		{
			vx = KOOPA_SHELL_VELOCITY_X;
		}
		else {
			vx = -KOOPA_SHELL_VELOCITY_X;
		}
		break;
	case KOOPA_STATE_RECOVER:
		_dieStart = 0;
		die = 0;
		StartRecover();
	}
}

void CKoopas::SetAnimation()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(KOOPA_ANI);
	SetAnimationSet(ani_set);
}

void CKoopas::UpdateShellPosition()
{
	if (player->nx > 0)
	{
		x = player->x + VALUE_ADJUST_SHELL + 20;
		if (player->level != MARIO_LEVEL_RACOON)
		{
			x = player->x + VALUE_ADJUST_SHELL + 2;
		}
	}
	else {
		x = player->x - VALUE_ADJUST_SHELL;
	}

	y = player->y;
	if (player->level != MARIO_LEVEL_SMALL) y = player->y + VALUE_ADJUST_SHELL+2;
}