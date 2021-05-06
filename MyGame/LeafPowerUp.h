#pragma once
#include "PowerUp.h"

#define LEAF_ANI	27

#define LEAF_DEFLECT_SPEED	0.5f
#define LEAF_VELOCITY_X     0.3f

#define LEAF_STATE_GO_UP	100
#define LEAF_STATE_FALLING	200

#define FLOATING_TIME 100

class CLeafPowerUp : public CPowerUp
{
	int changeDirection =0;
	int direction = 1;
	DWORD changeDirection_start;
public:
	CLeafPowerUp(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartChangeDirection() { changeDirection = 1; changeDirection_start = GetTickCount64(); }
};