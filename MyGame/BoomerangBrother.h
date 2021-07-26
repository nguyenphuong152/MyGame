#pragma once
#include "Enemy.h"
#include "Utils.h"

#define BOOMERANGBROTHER_WALKING_SPEED		0.1f
#define BOOMERANGBROTHER_GRAVITY			0.0015f
#define BOOMERANGBROTHER_DEFLECT_SPEED		0.4f

#define BOOMERANGBROTHER_STATE_WALKING	100
#define BOOMERANGBROTHER_STATE_JUMPING	200
#define BOOMERANGBROTHER_STATE_DIE		300
#define BOOMERANGBROTHER_STATE_THROWING	400

#define BOOMERANGBROTHER_ANI_WALKING	0
#define BOOMERANGBROTHER_ANI_THROW_ARMY	1

#define BOOMERANGBROTHER_BBOX_WIDTH		49
#define BOOMERANGBROTHER_BBOX_HEIGHT	75

#define WALKING_TIME 800
#define DISABLE_THROWING_TIME 5000

#define THROWING_TIMES	2

#define DIETIME 500

class CBoomerangBrother : public CEnemy
{
	bool isOnGround;
	bool isWalking;
	ULONGLONG _startWalking;

	ULONGLONG _startThrowing;
	bool disableThrowing;
	int countingTime;

	void StartWalking() { isWalking = true; _startWalking = GetTickCount64(); }
	void ResetWalking() { isWalking = _startWalking = 0; }
	void StartThrowing() { _startThrowing = GetTickCount64(); disableThrowing = true; }
	void ResetThrowing() { disableThrowing = false; _startThrowing = 0; countingTime = 0; }

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();

	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
public:
	bool isHitted;
	int direction;

	CBoomerangBrother();
	void BoomerangBrotherJump();
	void BoomerangBrotherThrowBoomerang();
	void CheckDirection();
	virtual void SetState(int state);
};