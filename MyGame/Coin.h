#pragma once
#include "GameObject.h"

#define COIN_ANI			25

#define COIN_BBOX_WIDTH		36
#define COIN_BBOX_HEIGHT	42

#define COIN_STATE_JUMPING		10

#define COIN_ANI_JUMPING		0
#define COIN_ANI_SPINNING		1

#define COIN_DEFLECT_SPEED  0.8f
#define COIN_GRAVITY		0.002f


enum class CoinType {
	jumping_coin,
	spinning_coin
};

class CCoin : public CGameObject
{
	CoinType type;
public:
	CCoin(CoinType type, float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

