#pragma once
#include "GameObject.h"

#define  COIN_BBOX_WIDTH 16

#define COIN_STATE_APPEAR 10

#define COIN_ANI_APPEAR 0

class CCoin : public CGameObject
{
public:
	CCoin();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	//virtual void SetState(int state);
	//virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

