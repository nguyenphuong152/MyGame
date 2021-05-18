#pragma once
#include "GameObject.h"

enum class GroundType {
	normal_ground,
	hidden_ground
};

class CGround :public CGameObject
{
	int width;
	int height;
	GroundType type;
public:
	GroundType GetType() { return type; };
	CGround(float r, float b,GroundType type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


