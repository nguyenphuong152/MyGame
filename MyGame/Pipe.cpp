#include "Pipe.h"
#include "GameObject.h"
#include "Utils.h"

CPipe::CPipe(PipeType type)
{
	isEnable = true;
	this->type = type;
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PIPE_WIDTH;
	b = y + 10;
}

void CPipe::Render()
{
	RenderBoundingBox();
}


