#include "Card.h"
#include "Grid.h"
#include "Utils.h"
#include "Notification.h"


CCard::CCard() {
	isEnable = true;
	numbAni = 1;
	animated_start = 0;
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

	srand((unsigned)time(0));

	if (state == CARD_STATE_TOUCH)
	{
		numbAni = 1 + rand() % 3;
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

		if (GetTickCount64() - animated_start > CARD_ANIMATED_TIME)
		{
			isEnable = false;
			animated_start = 0;
			CNotification::GetInstance()->ShowNoti(numbAni);
		}
	}
	grid_->Move(this);
}
