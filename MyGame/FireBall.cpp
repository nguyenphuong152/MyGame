﻿#include "Fireball.h"
#include "RedVenusFireTrap.h"
#include "Utils.h"
#include "Ground.h"
#include "Box.h"
#include "Camera.h"
#include "Brick.h"

CFireball::CFireball()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANI);
	SetAnimationSet(ani_set);
}

void CFireball::AllocateFireballToMario()
{
	SetPosition(CMario::GetInstance()->x+10, CMario::GetInstance()->y+20);
	isEnable = true;
	inUse = true;
	vx = CMario::GetInstance()->nx * FIREBALL_VELOCITY_X;
	vy = FIREBALL_VELOCITY_Y_NEAR;
}

void CFireball::AllocateFireballToVenus(int nx, float x, float y, bool isShootingUp)
{
	SetPosition(x,y);
	isEnable = true;
	inUse = true;
	this->isShootingUp = isShootingUp;
	vx = nx * FIREBALL_VELOCITY_X;
	vy = FIREBALL_VELOCITY_Y_NEAR;
}

void CFireball::Render()
{
	
	if (isEnable)
	{
		animation_set->at(0)->Render(0, x, y);
	}
	//RenderBoundingBox();
}


void CFireball::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {

	CGameObject::Update(dt, colObject);

	vy += FIREBALL_GRAVITY * dt;

	DisableFireballByCamera(colObject);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	if (state != FIREBALL_STATE_EXPLOSIVE)
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

		if (state != FIREBALL_STATE_EXPLOSIVE)
		{
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}

		//block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj) || dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny != 0)
				{
					vy = -FIREBALL_DEFLECT_Y;
				}
				else if (e->nx != 0) {
					SetState(FIREBALL_STATE_EXPLOSIVE);
					isEnable = false;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0) {
					SetState(FIREBALL_STATE_EXPLOSIVE);
					isEnable = false;
				}
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
	if (state == FIREBALL_STATE_EXPLOSIVE)
	{
		SetState(FIREBALL_STATE_FIRE);
	}
}

void CFireball::DisableFireballByCamera(vector<LPGAMEOBJECT>* listObject)
{
	for (UINT i = 0; i < listObject->size(); i++)
	{
		if (dynamic_cast<CCamera*>(listObject->at(i)))
		{
			CCamera* cam = dynamic_cast<CCamera*>(listObject->at(i));
			if (AABB(cam) == false) {
				isEnable = false;
			}
		}
	}
}

bool CFireball::FinishShooting()
{
	if (!inUse) return false;
	else if (!isEnable)
	{
		inUse = false;
		return true;
	}
	else return false;
}

//DebugOut(L"enable-x-y %d  %f %f \n", isEnable, x, y);
	//int dir = -1;
	//if (isShootingUp) dir = 1;

	//if (player->x > RANGE_X_LEFT&&player->x< RANGE_X_RIGHT) {
	//	vy = dir * FIREBALL_VELOCITY_Y_NEAR * vx;

	//}
	//else vy = dir * FIREBALL_VELOCITY_Y_FAR * vx;

	//// check lại vx nếu k khi con này quay phải, vy sẽ bị ngược chiều
	//if (vx > 0) vy = -vy;
