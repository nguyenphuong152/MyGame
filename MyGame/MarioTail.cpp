#include "MarioTail.h"
#include "Mario.h"
#include "Utils.h"

CMarioTail::CMarioTail()
{
	isEnable = false;
}

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	//vy = CMario::GetInstance()->vy;
	CGameObject::Update(dt, colObject); 

	vx = CMario::GetInstance()->vx;
	DebugOut(L"%f ---- mario %f \n", vx, CMario::GetInstance()->vx);
	//vy = CMario::GetInstance()->vy;

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colObject, coEvents);

	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny = 0;
		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + 0.4f;
		y += min_ty * dy + 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	
}

void CMarioTail::Render()
{
	RenderBoundingBox();
}

void CMarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 20;
	b = y + 25;
}
