#pragma once
#include "GameObject.h"

#define CHEST_STATE_UNTOUCH	0
#define CHEST_STATE_TOUCHED	1

#define CHEST_ANI_UNTOUCH	0
#define CHEST_ANI_TOUCHED	1

#define CHEST_BBOX_WIDTH	96

#define CHEST_ANI	50

class CChest :public CGameObject
{
	CGameObject* item;
public:
	CChest(CGameObject* item);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
