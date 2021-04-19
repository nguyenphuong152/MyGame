#include "Items.h"


CItems::CItems(CMario*player)
{
	isEnable = false;
	timeAppear = -1;
	this->player = player;
}

void CItems::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CGameObject::Update(dt, colObject);
	
	//xét thời gian tồn tại của một item,nếu thời gian hiện tại - thời gian xuất hiện lớn hơn thời gian tồn tại, tắt enable
	if (timeAppear == -1)
		timeAppear = GetTickCount();
	else
	{
		if (state != ITEM_MUSHROOM)
		{
			DWORD now = GetTickCount();
			if (now - timeAppear >= ITEM_TIME_ALIVE)
			{
				isEnable = false;
			}
		}
	}

	if (state != ITEM_MUSHROOM) vy += ITEM_GRAVITY * dt;

	if (state == ITEM_MUSHROOM)
	{

		//neu cay nam di len tren vien gach vua du, cay nam di ngang
		if (y < start_y - BRICK_BBOX_HEIGHT && vx == 0)
		{
			vy = -vy;
			vy += MUSHROOM_GRAVITY * dt;
			//check thang mario de xem di chuyen qua trai hay phai
			if (player->nx == 1) vx = -MUSHROOM_VELOCITY_X;
			else vx = MUSHROOM_VELOCITY_X;
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();
	CalcPotentialCollisions(colObject, coEvents);

	if (coEvents.size() == 0)
	{
		//di xuyen qua theo chieu y
		y += dy;
		x += dx;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		x += dx;
		//x += min_tx * dx + nx * 0.0001f;
		y += min_ty * dy + ny * 0.001f;

		for (UINT i = 0;i < coEventsResult.size();i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

		/*	if (dynamic_cast<CPipe*>(e->obj) && state == ITEM_MUSHROOM)
			{
				vx = MUSHROOM_VELOCITY_X * nx;
			}*/
		}

		for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];

	}
	
}

void CItems::Render()
{
	if (isEnable)
	{
		//DebugOut(L"render \n");
		animation_set->at(ITEM_ANI)->Render(0, x, y);
	}
	//RenderBoundingBox();
}

void CItems::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + ITEM_BBOX_WIDTH;
	b = y + ITEM_BBOX_HEIGHT;
}

void CItems::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case ITEM_COIN:
		vy = - COIN_VELOCITY_Y;
		break;
	case ITEM_MUSHROOM:
		start_y = y;
		vy = -MUSHROOM_VELOCITY_Y;
		break;
	}
}