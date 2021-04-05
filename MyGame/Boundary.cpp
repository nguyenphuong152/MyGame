#include "Boundary.h"
#include "Textures.h"
#include "Game.h"

CBoundary::CBoundary(float l, float t, float width, float height)
{
	x = l;
	y = t;
	this->width = width;
	this->height = height;
	isEnable = true;
}

void CBoundary::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CBoundary::Render()
{
	RenderBoundingBox();
}

