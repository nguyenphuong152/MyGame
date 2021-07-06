#pragma once
#include "Mario.h"
#include "GameObject.h"

#define WOOD_BLOCK_BBOX_WIDTH 48

#define WOOD_BLOCK_STATE_UNTOUCH 10
#define WOOD_BLOCK_STATE_TOUCHED 20

#define WOOD_BLOCK_ANI_UNTOUCH 0
#define WOOD_BLOCK_ANI_TOUCHED 1

#define WOOD_BLOCK_ANI			48

#define WOOD_BLOCK_SPEED		0.5f
#define WOOD_BLOCK_TURNBACK_SPEED	0.1f

class CWoodBlock :public CGameObject
{
	float dir;
	CGameObject* item;
	float oldX; //vi tri ban dau cua block
public:
	CWoodBlock(CGameObject* item, float x);

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state, float dir);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

