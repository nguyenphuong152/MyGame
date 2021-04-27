#pragma once
#include "GameObject.h"
class CObjectBoundary :public CGameObject
{
	int width;
	int height;
public:
	CObjectBoundary(float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};