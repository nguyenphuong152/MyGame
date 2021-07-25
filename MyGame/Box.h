#pragma once
#include "GameObject.h"

enum class BoxType {
	normal,
	special
};


class CBox :public CGameObject
{
	float width;
	float height;

	BoxType type;
public:
	BoxType GetType() { return this->type; };
	CBox( float r, float b, BoxType type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};
