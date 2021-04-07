#include "Ground.h"
#include "Textures.h"
#include "Game.h"

CGround::CGround(float l, float t, float width, float height)
{
	x = l;
	y = t+2;
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
	
}

