#include "Pipe.h"
#include "GameObject.h"

CPipe::CPipe(float l, float t, float r, float b)
{
	x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;
	isEnable = true;
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + width;
	b = y + height;
}

void CPipe::Render()
{
	RenderBoundingBox();
}


