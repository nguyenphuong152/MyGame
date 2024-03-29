#pragma once
#include "RedVenusFireTrap.h"

#define GREEN_VENUS_BBOX_HEIGHT		78

#define GREEN_POSITION_PIPE_X				5520
#define GREEN_POSITION_PIPE_Y				1110

#define GREEN_TIME_SHOOTING				800
#define GREEN_VENUS_MOVING_TIME			2500

#define GREEN_FIREBALL_POSITION_X			5520
#define GREEN_FIREBALL_POSITION_Y			344

class CGreenVenusFireTrap : public CRedVenusFireTrap
{
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
public:
	CGreenVenusFireTrap();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartShooting();
	void CheckDirection();
};