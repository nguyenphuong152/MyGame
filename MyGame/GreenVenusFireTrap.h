#pragma once
#include "RedVenusFireTrap.h"

#define GREEN_VENUS_FIRETRAP_ANI	63

#define POSITION_PIPE_X				5521
#define POSITION_PIPE_Y				1105

#define DOWN		0
#define UP			1
#define SHOOT_DOWN	2
#define SHOOT_UP		3

#define TIME_SHOOTING				800

#define FIREBALL_POSITION_X			5521
#define FIREBALL_POSITION_Y			344

class CGreenVenusFireTrap : public CRedVenusFireTrap
{
public:
	CGreenVenusFireTrap();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartShooting();
	void CheckDirection();
	void SetAnimation();
};