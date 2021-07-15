#pragma once
#include "GameObject.h"


class CBox :public CGameObject
{
	float width;
	float height;
public:
	CBox( float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
