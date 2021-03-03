#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"
#include "FireBallPool.h"

#define RED_VENUS_STATE_GO_DOWN		100
#define RED_VENUS_STATE_GO_UP		200
#define RED_VENUS_STATE_SHOOT_DOWN	300
#define RED_VENUS_STATE_SHOOT_UP	400

#define RED_VENUS_ANI_GO_DOWN		0
#define RED_VENUS_ANI_GO_UP	1
#define RED_VENUS_ANI_SHOOT_DOWN	2
#define RED_VENUS_ANI_SHOOT_UP	3

#define RED_VENUS_BBOX_WIDTH	16	
#define RED_VENUS_BBOX_HEIGHT	31

#define RED_VENUS_VELOCITY_Y 0.03f

#define POSITION_MIDDLE_SHOOTING 352
#define POSITION_MIDDLE_MOVING 353
#define POSITION_PIPE 370
#define POSITION_MOVING 339

#define TIME_SHOOTING 2000

class CRedVenusFireTrap : public CGameObject
{
	CMario* player;
	DWORD startShooting = -1;
	CFireBallPool *pool;

public:
	bool isGoingUp;
	bool isShooting;
	bool hasFireBall;

	CRedVenusFireTrap(CMario* player);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartShooting();
	void CheckDirection();
};

