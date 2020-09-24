#pragma once
#include "GameObject.h"
class CPipe : public CGameObject
{
	int width;
	int height;
public:
	CPipe(float t, float l, float r, float b);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

