#include "Ground.h"
#include "Textures.h"
#include "Game.h"

CGround::CGround(float width, float height)
{
	this->width = width;
	this->height =height;
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
	//RenderBoundingBox();
}

