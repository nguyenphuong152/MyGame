#pragma once
#include "GameObject.h"

#define SWITCH_STATE_UNTOUCH	0
#define SWITCH_STATE_TOUCHED	1

#define SWITCH_ANI_UNTOUCH	0
#define SWITCH_ANI_TOUCHED	1

#define SWITCH_BBOX_WIDTH	49
#define SWITCH_BBOX_HEIGHT_TOUCHED	19

class CSwitch :public CGameObject
{
public:
	CSwitch();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
