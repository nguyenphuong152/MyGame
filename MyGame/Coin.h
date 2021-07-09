#pragma once
#include "GameObject.h"

#define COIN_ANI			25

#define COIN_BBOX_WIDTH		30
#define COIN_BBOX_HEIGHT	42

#define COIN_STATE_JUMPING		10
#define STATE_DIE				20		

#define COIN_ANI_JUMPING		0
#define COIN_ANI_SPINNING		1

#define COIN_DEFLECT_SPEED  0.8f
#define COIN_GRAVITY		0.002f

#define JUMPING_TIME	700


enum class CoinType {
	jumping_coin,
	spinning_coin
};

class CCoin : public CGameObject
{
	bool isActive = false;
	CoinType type;

	DWORD jump_start;
	int jumping;

public:
	CCoin(CoinType type, float x, float y);

	void StartJumping() { jumping = 1; jump_start = GetTickCount64(); }
	void ResetJumping() { jumping = jump_start = 0; }

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

