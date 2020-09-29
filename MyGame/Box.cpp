#include "Box.h"
#include "Textures.h"
#include "Game.h"

CBox::CBox(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
}

void CBox::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CBox::Render()
{
	//RenderBoundingBox();
}

