#include "Pipe.h"
#include "GameObject.h"

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
	b = y + PIPE_WIDTH;
}

void CPipe::Render()
{
	RenderBoundingBox();
}


