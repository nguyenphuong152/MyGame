#include "Pipe.h"
#include "GameObject.h"
#include "Utils.h"

CPipe::CPipe(PipeType type,float width, float height)
{
	this->width = width;
	this->height = height;
	isEnable = true;
	this->type = type;
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


