#include "Boomerang.h"
#include "Game.h"
#include "Utils.h"
#include "ObjectBoundary.h"
#include "Box.h"

CBoomerang::CBoomerang()
{
	_state.live.inUse = false;
}

void CBoomerang::StartThrowing(CBoomerangBrother* bBrother)
{
	CMario* player = CGame::GetInstance()->GetPlayer();

	isEnable = true;
	_state.live.inUse = true;
	_state.live.changeDirection = false;

	SetBoomerangBrother(bBrother);
	SetPosition(bBrother->x, bBrother->y - 30);

	_state.live.start_x = bBrother->x;
	nx = bBrother->nx;

	vx = nx * BOOMERANG_VELOCITY_X;
	vy = -BOOMERANG_VELOCITY_Y;

}

void CBoomerang::Render()
{
	animation_set->at(0)->Render(1, 1, x, y);
	//RenderBoundingBox();
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	CGameObject::Update(dt, colObject);

	if (nx > 0) {
		vx -= BOOMERANG_TURNBACK_SPEED;
	}
	else {
		vx += BOOMERANG_TURNBACK_SPEED;
	}

	vy += BOOMERANG_GRAVITY;
	
	if (nx < 0 && vx > 0)
	{
		_state.live.changeDirection = true;
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colObject, coEvents);

	//if no collision occured, proceed normally
	if (coEvents.size() == 0 )
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;
		
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		////block every object first
		//x += min_tx * dx + nx * 0.4f;
		//y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CObjectBoundary*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (e->nx < 0)
					{
						if (this->nx < 0)
						{
							DisableBoomerang();
						}
						else {
							vx = BOOMERANG_VELOCITY_X;
						}
					}
					else if (e->nx > 0)
					{
						if (this->nx > 0)
						{
							DisableBoomerang();
						}
						else {
							vx = -BOOMERANG_VELOCITY_X;
						}
					}
					
					x += dx;
				}
			}
			else if (dynamic_cast<CBoomerangBrother*>(e->obj))
			{
				CBoomerangBrother* bBrother = dynamic_cast<CBoomerangBrother*>(e->obj);
				if (e->nx != 0||e->ny!=0)
				{
					bBrother->isHitted = true;
					DisableBoomerang();
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CBoomerang::DisableBoomerang()
{
	_state.live.bBrother->isHitted = true;
	_state.live.changeDirection = false;
	isEnable = false;
}

void CBoomerang::DisableBoomerangByCamera()
{

	CCamera* cam = CGame::GetInstance()->GetMainCamera();
	if (AABB(cam) == false) {
		DisableBoomerang();
	}
}

void CBoomerang::ChangeBoomerangDirection()
{
	this->nx = -this->nx;
	vx = -vx;
	vy = BOOMERANG_VELOCITY_Y / 2;
	_state.live.changeDirection = true;
}

void CBoomerang::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + BOOMERANG_BBOX_WIDTH;
	b = t + BOOMERANG_BBOX_WIDTH;
}

void CBoomerang::SetState(int state)
{
	CGameObject::SetState(state);
}

bool CBoomerang::FinishShooting()
{
	if (!_state.live.inUse) return false;
	else if (!isEnable)
	{
		_state.live.inUse = false;
		return true;
	}
	else return false;
}



