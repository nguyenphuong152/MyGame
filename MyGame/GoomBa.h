#pragma once
#include "Enemy.h"

#define GOOMBA_WALKING_SPEED	0.05f
#define GOOMBA_GRAVITY			0.0015f
#define GOOMBA_DEFLECT_SPEED    0.6f
#define GOOMBA_BBOX_WIDTH		50
#define GOOMBA_BBOX_HEIGHT		51
#define GOOMBA_BBOX_HEIGHT_DIE	30

#define GOOMBA_LEVEL_2					2
#define GOOMBA_LEVEL_1					1

#define GOOMBA_STATE_WALKING			100
#define GOOMBA_STATE_DIE				200
#define GOOMBA_STATE_DIE_WITH_DEFLECT	300

#define GOOMBA_ANI_WALKING				0
#define GOOMBA_ANI_DIE					1

#define GOOMBA_DIE_TIME		700


class CGoomBa : public CEnemy
{
protected:
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CGoomBa();

	virtual void SetState(int state);
};

