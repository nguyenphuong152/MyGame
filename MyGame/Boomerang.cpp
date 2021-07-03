#include "Boomerang.h"
#include "Game.h"
#include "Utils.h"

CBoomerang::CBoomerang()
{
	_state.live.inUse = false;
}

void CBoomerang::StartThrowing(CBoomerangBrother *bBrother)
{
	CMario* player = CGame::GetInstance()->GetPlayer();

	isEnable = true;
	_state.live.inUse = true;

	SetPosition(bBrother->x + 10, bBrother->y + 20);

	vx = -BOOMERANG_VELOCITY_X;
	vy = -BOOMERANG_VELOCITY_Y_NEAR;
}

void CBoomerang::Render()
{
	DebugOut(L"vo \n");
	animation_set->at(0)->Render(1, 1, x, y);
	//RenderBoundingBox();
}


void CBoomerang::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {

	CGameObject::Update(dt, colObject);

	vy += BOOMERANG_GRAVITY * dt;

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

		//block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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



