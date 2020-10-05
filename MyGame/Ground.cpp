#include "Ground.h"
#include "Textures.h"
#include "Game.h"

CGround::CGround(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
	isEnable = true;
}

void CGround::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CGround::Render()
{
	RenderBoundingBox();
}

