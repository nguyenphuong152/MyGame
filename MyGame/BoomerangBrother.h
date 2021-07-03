#pragma once
#include "Enemy.h"

#define BOOMERANGBROTHER_WALKING_SPEED		0.1f
#define BOOMERANGBROTHER_GRAVITY			0.0015f
#define BOOMERANGBROTHER_DEFLECT_SPEED		0.4f

#define BOOMERANGBROTHER_STATE_WALKING	100
#define BOOMERANGBROTHER_STATE_JUMPING	200
#define BOOMERANGBROTHER_STATE_DIE		300

#define BOOMERANGBROTHER_ANI_WALKING	0
#define BOOMERANGBROTHER_ANI_THROW_ARMY	1

#define BOOMERANGBROTHER_BBOX_WIDTH		49
#define BOOMERANGBROTHER_BBOX_HEIGHT	75

#define WALKING_TIME 300


class CBoomerangBrother : public CEnemy
{
	bool isOnGround;
	int direction;
	DWORD _startWalking;

	void StartWalking() { isOnGround = true; _startWalking = GetTickCount64(); }
	void ResetWalking() { isOnGround = false; _startWalking = 0; }

public:
	CBoomerangBrother();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
};