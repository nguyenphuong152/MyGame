#include "Decoration.h"

CDecoration::CDecoration(Type type)
{
	this->type = type;
	isEnable = true;
}

void CDecoration::Render()
{
	animation_set->at(0)->Render(-1, 1, x, y);
	//RenderBoundingBox();
}

void CDecoration::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = b = 0;
}