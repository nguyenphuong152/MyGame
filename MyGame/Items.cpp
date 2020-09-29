#include "Items.h"
#include "Utils.h"
#include "Brick.h"

CItems::CItems()
{
	timeAppear = -1;
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CGameObject::Update(dt,colObject);

	//xét thời gian tồn tại của một item,nếu thời gian hiện tại - thời gian xuất hiện lớn hơn thời gian tồn tại, tắt enable
	if (timeAppear == -1)
		timeAppear = GetTickCount();
	else
	{
		DWORD now = GetTickCount();
		if (now - timeAppear > ITEM_TIME_ALIVE)
		{
			SetEnable(false);
			return;
		}
	}
	

	vy += ITEM_GRAVITY * dt;

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
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		//collision logic with other objects
		for (UINT i = 0;i < coEventsResult.size();i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			/*if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny >0)
				{
					SetEnable(false);
				}

			}*/
		}
	}

	//DebugOut(L"[INFO]vy: %f \n", vy);

	for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];
	
}

void CItems::Render()
{
	int ani=-1;

	if (IsEnable())
	{
		if (state == ITEM_COIN)
		{
			ani = ITEM_COIN_ANI;
		}

		animation_set->at(ani)->Render(1, x, y);
	}

}

void CItems::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	switch (state)
	{
	case ITEM_COIN:
		r = x + ITEM_COIN_BBOX_WIDTH;
		b = y + ITEM_COIN_BBOX_WIDTH;
	break;
	}
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_COIN:
		vy = - COIN_VELOCITY;
		break;
	}
}