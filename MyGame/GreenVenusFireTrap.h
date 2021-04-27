#pragma once
#include "RedVenusFireTrap.h"

#define GREEN_VENUS_BBOX_HEIGHT		78

#define POSITION_PIPE_X				5520
#define POSITION_PIPE_Y				1110

#define TIME_SHOOTING				800

#define FIREBALL_POSITION_X			5520
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
};