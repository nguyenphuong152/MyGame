#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"

#define RED_VENUS_STATE_GO_DOWN		100
#define RED_VENUS_STATE_GO_UP		200
#define RED_VENUS_STATE_SHOOT_DOWN	300
#define RED_VENUS_STATE_SHOOT_UP	400

#define RED_VENUS_FIRETRAP_ANI		60
#define RED_VENUS_ANI_GO_DOWN		0
#define RED_VENUS_ANI_GO_UP			1
#define RED_VENUS_ANI_SHOOT_DOWN	2
#define RED_VENUS_ANI_SHOOT_UP		3

#define RED_VENUS_BBOX_WIDTH		45	
#define RED_VENUS_BBOX_HEIGHT		94

#define RED_VENUS_VELOCITY_Y		0.05f

#define POSITION_MIDDLE_SHOOTING	352
#define POSITION_MIDDLE_MOVING		353
#define POSITION_PIPE_X				1040
#define POSITION_PIPE_Y				1105
#define POSITION_MOVING				339

#define TIME_SHOOTING				800

#define FIREBALL_POSITION_X			360
#define FIREBALL_POSITION_Y			344

class CRedVenusFireTrap : public CGameObject
{
	DWORD startShooting = -1;
	bool isShooting;

public:

	CRedVenusFireTrap();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartShooting();
	void CheckDirection();
	void SetAnimation();
};

