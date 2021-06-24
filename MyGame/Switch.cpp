#include "Switch.h"

CSwitch::CSwitch() {
	isEnable = false;
	SetState(SWITCH_STATE_UNTOUCH);
}

void CSwitch::Render()
{
	int ani = -1;
	if (state == SWITCH_STATE_UNTOUCH)
	{
		ani = SWITCH_ANI_UNTOUCH;
	}
	else if (state == SWITCH_STATE_TOUCHED)
	{
		ani = SWITCH_ANI_TOUCHED;
	}
	animation_set->at(ani)->Render(-1,1, x, y);
	//RenderBoundingBox();
}

void CSwitch::SetState(int state)
{
	CGameObject::SetState(state);
}

void CSwitch::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + SWITCH_BBOX_WIDTH;
	b = y + SWITCH_BBOX_WIDTH;
	if (state == SWITCH_STATE_TOUCHED)
	{
		b = y + SWITCH_BBOX_HEIGHT_TOUCHED;
	}
}

void CSwitch::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
}
