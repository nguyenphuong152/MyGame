#include "PowerUp.h"

void CPowerUp::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CGameObject::Update(dt, colObject);
}

void CPowerUp::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + POWER_UP_BBOX_WIDTH;
	b = y + POWER_UP_BBOX_WIDTH;
}

void CPowerUp::SetState(int state)
{
	CGameObject::SetState(state);
}

void CPowerUp::Render()
{

}
