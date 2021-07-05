#pragma once
#include "Mario.h"
#include "GameObject.h"

#define BRICK_BBOX_WIDTH 48

#define BRICK_STATE_UNTOUCH 10
#define BRICK_STATE_TOUCHED 20

#define BRICK_ANI_UNTOUCH 0
#define BRICK_ANI_TOUCHED 1

#define BRICK_ANI			22
#define TWINKLE_BRICK_ANI	23

#define BRICK_VELOCITY_Y		0.5f
#define BRICK_DROP_VELOCITY_Y	0.005f

#define NUMBER_OF_COINS		10

enum class BrickType {
	question_brick,
	twinkle_brick,
	twinkle_brick_no_item,
	twinkle_brick_coin
};

class CBrick :public CGameObject
{
	int coinCounts = 0;

	CGameObject* item;
	BrickType type;
	float oldY; //lưu lại vị trí để cục gạch nhảy lên một xíu khi mario đụng vô
public:

	CBrick(CGameObject* item,float y, BrickType type);
	CBrick(float y, BrickType type);
	BrickType GetType() { return type; };

	vector<CGameObject*> coins;

	void SetAttackedAnimation();

	int GetCoinCounts() { return coinCounts; }
	void IncreaseCoinCounts() { coinCounts++; };

	void AddCoins(CGameObject* coin);
	void DisableBrick();
	bool isTouch;

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

