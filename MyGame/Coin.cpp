#include "Coin.h"

CCoin::CCoin()
{
	SetState(COIN_STATE_APPEAR);
}

void CCoin::Render()
{
	int ani = COIN_ANI_APPEAR;
	animation_set->at(ani)->Render(1,x,y);
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_WIDTH;
}