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
	//DebugOut(L"hello \n");
	animation_set->at(0)->Render(1, 1, x, y);
	//RenderBoundingBox();
}

void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	colObject->push_back(this);
	CGameObject::Update(dt, colObject);

	if (nx > 0) {
		vx -= BOOMERANG_TURNBACK_SPEED;
	}
	else {
		vx += BOOMERANG_TURNBACK_SPEED;
	}

	if (_state.live.bBrother->GetState() == BOOMERANGBROTHER_STATE_DIE) DisableBoomerang();

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
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult,nx,ny);

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
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny != 0) y += dy;
				else if (e->nx != 0)  x += dx;
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

	DisableBoomerangByCamera();

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
	b = t + BOOMERANG_BBOX_WIDTH +6;
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



