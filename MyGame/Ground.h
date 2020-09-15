#pragma once
#include "GameObject.h"

#define GROUND_BBOX_WIDTH 16
#define GROUND_BBOX_HEIGHT 16

class CGround :public CGameObject
{
	float pos_x, pos_y;
public:
	CGround(float pos_x, float pos_y) { this->pos_x = pos_x; this->pos_y = pos_y; }
	void RenderGround(float pos_x, float pos_y);
};


