#pragma once
#include "GameObject.h"
class CObjectBoundary :public CGameObject
{
	float width;
	float height;
public:
	CObjectBoundary(float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};