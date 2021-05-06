#pragma once
#include "GameObject.h"

#define POWER_UP_BBOX_WIDTH		49
#define POWER_UP_GRAVITY		0.003f

#define POWER_UP_ANI			0

class CPowerUp : public CGameObject
{
protected:
	float start_y;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state) ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};