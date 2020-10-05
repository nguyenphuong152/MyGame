#pragma once
#include"GameObject.h"
#include "Utils.h"
#include "Brick.h"
#include "Pipe.h"
#include "Mario.h"
#include "Ground.h"

#define ITEM_COIN 100 
#define ITEM_LEAF 101
#define ITEM_MUSHROOM 102

#define ITEM_ANI 0

#define ITEM_BBOX_WIDTH 16
#define ITEM_BBOX_HEIGHT 16

#define COIN_VELOCITY_Y 0.5f

#define ITEM_GRAVITY 0.002f
#define MUSHROOM_GRAVITY 0.04f

#define MUSHROOM_VELOCITY_Y 0.007f
#define MUSHROOM_VELOCITY_X 0.05f

#define ITEM_TIME_ALIVE 500


class CItems : public CGameObject
{
	//tao player de get huong cho mushroom
	CMario* player;
	DWORD timeAppear;
	float start_y;

public:
	
	CItems(CMario*player);
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};

