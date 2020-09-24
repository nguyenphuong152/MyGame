#include "Brick.h"
#include "Utils.h"
#include "Mario.h"

CBrick::CBrick()
{
	SetState(BRICK_STATE_UNTOUCH);
}

void CBrick::Render()
{
	int ani;
	if (state == BRICK_STATE_UNTOUCH)
	{
		ani = BRICK_ANI_UNTOUCH;
	}
	else if (state == BRICK_STATE_TOUCHED)
	{
		ani = BRICK_ANI_TOUCHED;
	}
	animation_set->at(ani)->Render(0, x, y);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == BRICK_STATE_TOUCHED)
	{
		oldY = y;
		y = oldY-BRICK_DEFLECT_POS;
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == BRICK_STATE_TOUCHED)
	{
		if (y < oldY)
			y+=3;
	}

	
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}
