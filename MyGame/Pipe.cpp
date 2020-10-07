#include "Pipe.h"
#include "GameObject.h"

CPipe::CPipe(int spritePipe)
{
	/*x = l;
	y = t;
	width = r - l + 1;
	height = b - t + 1;*/
	this->spritePipe = spritePipe;
	isEnable = true;
}

void CPipe::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + 16;
	b = y + 16;
}

void CPipe::Render()
{
	CSprites::GetInstance()->Get(spritePipe)->Draw(0,x, y);
}


