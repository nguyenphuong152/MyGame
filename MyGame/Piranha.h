#pragma once
#include "RedVenusFireTrap.h"

#define PIRANHA_STATE_GO_UP 100
#define PIRANHA_STATE_GO_DOWN 200

#define PIRANHA_BBOX_WIDTH	50
#define PIRANHA_BBOX_HEIGHT	75

#define PIRANHA_VELOCITY_Y		0.05f

#define PIRANHA_ANI_ACTIVE	0

#define PIRANHA_PIPE_POSITION_Y		1155

#define ACTIVE_TIME			1800

class CPiranha : public CRedVenusFireTrap
{
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
public:
	CPiranha();
	virtual void SetState(int state);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
