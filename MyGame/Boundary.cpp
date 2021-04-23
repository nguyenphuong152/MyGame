#include "Boundary.h"
#include "Textures.h"
#include "Game.h"

CBoundary::CBoundary( float width, float height)
{
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
	//RenderBoundingBox();
}

