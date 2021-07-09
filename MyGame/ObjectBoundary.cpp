#include "ObjectBoundary.h"
#include "Textures.h"
#include "Game.h"

CObjectBoundary::CObjectBoundary(float width, float height)
{
	this->width = width;
	this->height = height;
	isEnable = true;
}

void CObjectBoundary::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CObjectBoundary::Render()
{
	RenderBoundingBox();
}

