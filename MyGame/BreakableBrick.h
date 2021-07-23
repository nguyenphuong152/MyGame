#pragma once
#include "GameObject.h"
#include "Mario.h"

#define BREAKABLE_BRICK_ANI			23

#define BREAKABLE_BRICK_VISUAL_STATE      10
#define BREAKABLE_BRICK_TOUCHED_STATE	  11
#define BREAKABLE_BRICK_COIN_STATE		  12

#define BREAKABLE_BRICK_VISUAL_ANI      0
#define BREAKABLE_BRICK_TOUCHED_ANI	    1
#define BREAKABLE_BRICK_COIN_ANI		2 

#define BREAKABLE_BRICK_BBOX_WIDTH	48

#define TIME_IN_COIN_STATE		5000

class CBreakableBrick : public CGameObject
{
	CMario* player;

	int coinState;
	ULONGLONG coinstate_Start;

	void StartCoinState() { coinState = 1; coinstate_Start = GetTickCount64(); };
	void ResetCoinState() { coinState = 0; coinstate_Start = 0; };
public:
	CBreakableBrick(float x, float y);
	void SetAttackedAnimation();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};