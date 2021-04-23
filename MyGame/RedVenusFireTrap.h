#pragma once
#include "GameObject.h"
#include "Utils.h"
#include "Mario.h"

#define VENUS_STATE_GO_DOWN		100
#define VENUS_STATE_GO_UP		200
#define VENUS_STATE_SHOOT_DOWN	300
#define VENUS_STATE_SHOOT_UP	400

#define VENUS_FIRETRAP_ANI		60
#define VENUS_ANI_GO_DOWN		0
#define VENUS_ANI_GO_UP			1
#define VENUS_ANI_SHOOT_DOWN	2
#define VENUS_ANI_SHOOT_UP		3

#define VENUS_BBOX_WIDTH		45	
#define VENUS_BBOX_HEIGHT		94

#define VENUS_VELOCITY_Y		0.05f

#define POSITION_PIPE_X				1040
#define POSITION_PIPE_Y				1105

#define TIME_SHOOTING				800

#define FIREBALL_POSITION_X			360
#define FIREBALL_POSITION_Y			344

class CRedVenusFireTrap : public CGameObject
{
protected:
	DWORD startShooting = -1;
	bool isShooting;
	bool isShootingUp;

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

