﻿#include "Fireball.h"
#include "RedVenusFireTrap.h"
#include "Utils.h"
#include "Ground.h"
#include "Box.h"
#include "Camera.h"
#include "Brick.h"
#include "Effect.h"
#include "EffectPool.h"
#include "Boundary.h"
#include "Game.h"
#include "BreakableBrick.h"

CFireball::CFireball()
{
	_state.live.isBelongToVenus = false;
	_state.live.isShootingUp = false;
	_state.live.inUse = false;
	_state.live.alive_time = 0;
}

void CFireball::AllocateFireballToMario()
{
	CMario* player = CGame::GetInstance()->GetPlayer();
	isEnable = true;

	SetPosition(player->x+10, player->y+20);
	_state.live.inUse = true;
	_state.live.isBelongToVenus = false;

	vx = player->nx * FIREBALL_VELOCITY_X;
	vy = FIREBALL_VELOCITY_Y_NEAR;
	StartAlive();
}

void CFireball::AllocateFireballToVenus(int nx, float x, float y, bool isShootingUp)
{
	SetPosition(x,y);
	isEnable = true;

	_state.live.inUse = true;
	_state.live.isBelongToVenus = true;
	_state.live.isShootingUp = isShootingUp;

	vx = nx * FIREBALL_VELOCITY_X/2;
	vy = FIREBALL_VENUS_VELOCITY_Y_NEAR;
	StartAlive();
}

void CFireball::Render()
{
	animation_set->at(0)->Render(1,1, x, y);
	//RenderBoundingBox();
}


void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	
	colObject->push_back(this);

	CGameObject::Update(dt, colObject);

	vy += FIREBALL_GRAVITY * dt;

	DisableFireballByCamera();

	if (_state.live.isBelongToVenus) HandleFireballForVenus();

	if (GetTickCount64() - _state.live.alive_time > FIREBALL_ALIVE_TIME && _state.live.alive_time > 0)
	{
		isEnable = false;
		_state.live.alive_time = 0;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != FIREBALL_STATE_EXPLOSIVE)
		CalcPotentialCollisions(colObject, coEvents);

	//if no collision occured, proceed normally
	if (coEvents.size() == 0 || _state.live.isBelongToVenus == true)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float nx = 0, ny;
		if (state != FIREBALL_STATE_EXPLOSIVE)
		{
			FilterCollision(coEvents, coEventsResult,nx,ny);
		}


		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if(dynamic_cast<CEnemy*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0) {
					e->obj->isEnable = false;
					ExplosedFireball();
				}
			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny < 0) vy = -FIREBALL_DEFLECT_Y;
				if (e->nx != 0) x += dx;
			}
			else if (dynamic_cast<CCamera*>(e->obj) || dynamic_cast<CBoundary*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					isEnable = false;
				}
			}
			else {
				if (e->nx != 0) ExplosedFireball();
				if (e->ny < 0)  vy = -FIREBALL_DEFLECT_Y;
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CFireball::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireball::SetState(int state)
{
	CGameObject::SetState(state);
}

void CFireball::ExplosedFireball()
{
	isEnable = false;

	CEffect* effect = CEffectPool::GetInstance()->Create();
	if (effect != NULL)
	{
		effect->SetEffect(EffectName::fireball_explose,this);
	}
}

void CFireball::DisableFireballByCamera()
{
	CCamera* cam = CGame::GetInstance()->GetMainCamera();
	if (AABB(cam) == false) {
		isEnable = false;
	}
}

bool CFireball::FinishShooting()
{
	if (!_state.live.inUse) return false;
	else if (!isEnable)
	{
		_state.live.inUse = false;
		if (_state.live.isBelongToVenus) _state.live.isBelongToVenus = false;
		return true;
	}
	else return false;
}

void CFireball::HandleFireballForVenus()
{
	CMario* player = CGame::GetInstance()->GetPlayer();

	int dir = -1;
	if (_state.live.isShootingUp) dir = 1;

	if (player->x > RANGE_X_LEFT && player->x < RANGE_X_RIGHT)
	{
		vy = dir * FIREBALL_VENUS_VELOCITY_Y_NEAR * vx;
	}
	else {
		vy = dir * FIREBALL_VENUS_VELOCITY_Y_FAR * vx ;
	}

	if (vx > 0) vy = -vy;
}
	

	
