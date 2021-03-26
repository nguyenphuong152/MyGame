#pragma once
#include "GameObject.h"


class CBoundary :public CGameObject
{
	int width;
	int height;
public:
	CBoundary(float t, float l, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};