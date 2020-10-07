#pragma once
#include "GameObject.h"
class CPipe : public CGameObject
{
	int spritePipe;
public:
	CPipe(int spritePipe);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

