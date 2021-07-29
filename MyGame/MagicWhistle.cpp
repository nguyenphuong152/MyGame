#include "MagicWhistle.h"
#include "Utils.h"
#include "Game.h"

CMagicWhistle::CMagicWhistle()
{
	active_star = 0;
	isEnable = true;
	SetState(MAGIC_WHISTLE_STATE_INACTIVE);
	SetObjectAnimation(MAGIC_WHISTLE_ANI);
}

void CMagicWhistle::Render()
{
	if(state==MAGIC_WHISTLE_STATE_ACTIVE)
		animation_set->at(0)->Render(-1, 1, x, y);
}

void CMagicWhistle::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void CMagicWhistle::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MAGIC_WHISTLE_STATE_ACTIVE)
	{
		vy = -MAGIC_WHISTLE_SPEED;
		StartActive();
	}
}

void CMagicWhistle::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	if (state == MAGIC_WHISTLE_STATE_ACTIVE)
	{
		CGameObject::Update(dt);
		if (active_star > 0 && GetTickCount64() - active_star > MAGIC_WHISTLE_APPEARED_TIME)
		{
			vy = 0;
			CGame::GetInstance()->GetPlayer()->isEatMagicWhistle = true;
		}
		else {
			y += dy;
		}
	}
}
