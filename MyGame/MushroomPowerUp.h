#pragma once
#include "PowerUp.h"

#define RED_MUSHROOM_ANI		26
#define GREEN_MUSHROOM_ANI		28

#define MUSHROOM_STATE_GO_UP	100
#define MUSHROOM_STATE_WALKING  200

#define MUSHROOM_VELOCITY_X     0.2f
#define MUSHROOM_VELOCITY_Y		0.02f

class CMushroomPowerUp : public CPowerUp
{
	enum MushroomType {
		green_mushroom,
		red_mushroom
	};

public:
	CMushroomPowerUp(float x, float y, MushroomType typep);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};