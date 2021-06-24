﻿#pragma once
#include "Mario.h"
#include "GameObject.h"

#define BRICK_BBOX_WIDTH 49
#define BRICK_BBOX_HEIGHT 49

#define BRICK_STATE_UNTOUCH 10
#define BRICK_STATE_TOUCHED 20

#define BRICK_ANI_UNTOUCH 0
#define BRICK_ANI_TOUCHED 1

#define BRICK_ANI			22
#define TWINKLE_BRICK_ANI	23

#define BRICK_VELOCITY_Y		0.5f
#define BRICK_DROP_VELOCITY_Y	0.1f

enum class BrickType {
	question_brick,
	twinkle_brick
};

class CBrick :public CGameObject
{
	CGameObject* item;
	BrickType type;
	float oldY; //lưu lại vị trí để cục gạch nhảy lên một xíu khi mario đụng vô
public:

	CBrick(CGameObject* item,float y, BrickType type);
	BrickType GetType() { return type; };

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};

