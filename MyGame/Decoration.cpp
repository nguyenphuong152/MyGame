#include "Decoration.h"
#include "Ground.h"
#include "Utils.h"
#include "Game.h"

CDecoration::CDecoration(Type type)
{
	this->type = type;
	showing_start = 0;
	isEnable = true;
	dir = 1;

	if (type == Type::Dialog) StartShowing();
}

void CDecoration::Render()
{
	if (type == Type::Enemy)
	{
		animation_set->at(0)->Render(dir, 1, x, y);
	}
	else if (type == Type::Dialog &&CGame::GetInstance()->showDialog == true)
	{
		animation_set->at(1)->Render(-1, 1, x, y);
		CSprites::GetInstance()->Get(NUMBER_1)->Draw(-1, 1, NUMBER_1_POS_X, NUMBER_1_POS_Y);
		CSprites::GetInstance()->Get(NUMBER_4)->Draw(-1, 1, NUMBER_2_POS_X, NUMBER_2_POS_Y);
	}
	else if(type == Type::Help||type == Type::Tree) {
		animation_set->at(0)->Render(-1, 1, x, y);
	}
	
	//RenderBoundingBox();
}

void CDecoration::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x+42;
	b = y + 48;

	if (type == Type::Dialog) r = b = 0;
}

void CDecoration::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	if (type == Type::Enemy)
	{
		CGameObject::Update(dt);

		vx = -dir * ENEMY_WALKING_SPEED;
		//collision logic with other objects
		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObject, coEvents);

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
					if (e->nx != 0)
					{
						dir = -dir;
					}
				}
			}
		}
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else if (type == Type::Dialog && CGame::GetInstance()->showDialog == true)
	{
		CGame::GetInstance()->isFinish = true;
		if (showing_start > 0 && GetTickCount64() - showing_start > SHOWING_TIME)
		{
			CGame::GetInstance()->isFinish = false;
			isEnable = false;
		}
	}
}
