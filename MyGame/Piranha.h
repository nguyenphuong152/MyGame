#pragma once
#include "GameObject.h"

#define PIRANHA_STATE_ACTIVE 100

#define PIRANHA_BBOX_WIDTH	50
#define PIRANHA_BBOX_HEIGHT	75

#define PIRANHA_VELOCITY_Y		0.05f

#define PIRANHA_ANI_ACTIVE	0

#define PIPE_POSITION_Y		1087

#define ACTIVE_TIME			300

class CPiranha : public CGameObject
{
	int active;
	DWORD active_start;
public:
	CPiranha();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	void StartActive();
	void ResetActive();
};
