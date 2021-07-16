#include "Switch.h"
#include "Utils.h"
#include "Grid.h"

CSwitch::CSwitch() {
	SetPosition(SWITCH_POSITION_X, SWITCH_POSITION_Y);
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
	
	if (isEnable)
	{
		animation_set->at(ani)->Render(-1, 1, x, y);
		//RenderBoundingBox();
	}
	
	
}

void CSwitch::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == SWITCH_STATE_UNTOUCH)
	{
		isEnable = true;
	}
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
	grid_->Move(this);
}
