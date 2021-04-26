#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED	0.05f;

#define GOOMBA_BBOX_WIDTH		50
#define GOOMBA_BBOX_HEIGHT		51
#define GOOMBA_BBOX_HEIGHT_DIE	30

#define GOOMBA_STATE_WALKING			100
#define GOOMBA_STATE_DIE				200

#define GOOMBA_ANI_WALKING				0
#define GOOMBA_ANI_DIE					1
#define GOOMBA_ANI						3

#define GOOMBA_DIE_TIME		700

class CGoomBa : public CGameObject
{
protected:
	DWORD die_start;
	int die;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CGoomBa();
	virtual void SetState(int state);
	void StartDie() { die = 1; die_start = GetTickCount64(); }
};

