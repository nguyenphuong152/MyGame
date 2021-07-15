#pragma once
#include "GameObject.h"


class CBoundary :public CGameObject
{
	float width;
	float height;
public:
	CBoundary( float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};