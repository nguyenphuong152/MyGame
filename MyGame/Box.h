#pragma once
#include "GameObject.h"


class CBox :public CGameObject
{
	int width;
	int height;
public:
	CBox( float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
