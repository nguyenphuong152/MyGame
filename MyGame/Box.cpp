#include "Box.h"
#include "Textures.h"
#include "Game.h"

CBox::CBox(float width, float height, BoxType t)
{
	this->width = width;
	this->height = height;
	isEnable = true;
	this->type = t;
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

