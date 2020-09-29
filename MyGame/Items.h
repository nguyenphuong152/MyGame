#pragma once
#include"GameObject.h"

#define ITEM_COIN 100 
#define ITEM_LEAF 101
#define ITEM_MUSHROOM 102

#define ITEM_COIN_ANI 0

#define ITEM_COIN_BBOX_WIDTH 16

#define COIN_VELOCITY 0.5f
#define ITEM_GRAVITY 0.002f

#define ITEM_TIME_ALIVE 500


class CItems : public CGameObject
{
	DWORD timeAppear;
public:
	CItems();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

