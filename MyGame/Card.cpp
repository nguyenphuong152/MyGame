#include "Card.h"
#include "Utils.h"

CCard::CCard() {
	isEnable = true;
	SetState(CARD_STATE_UNTOUCH);
}

void CCard::Render()
{
	int ani = -1;
	if (state == CARD_STATE_UNTOUCH)
	{
		ani = CARD_RANDOM;
	}
	else if (state == CARD_STATE_TOUCH)
	{
		ani = numbAni;
	}
	animation_set->at(ani)->Render(-1, 1, x, y);
	RenderBoundingBox();
}

void CCard::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == CARD_STATE_TOUCH)
	{
		numbAni = 1 + rand() % (3 + 1 - 1);
		DebugOut(L"bunnn %d \n", numbAni);
		vy = -CARD_VELOCITY_Y;
		StartAnimated();
	}
}

void CCard::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + CARD_BBOX;
	b = y + CARD_BBOX;
}

void CCard::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == CARD_STATE_TOUCH)
	{
		vy += CARD_GRAVITY * dt;
		y += dy;

		if (GetTickCount64() - animated_start > ANIMATED_TIME)
		{
			isEnable = false;
			animated_start = 0;
		}
	}
}
