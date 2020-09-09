#pragma once
#include "GameObject.h"

#define GOOMBA_WALKING_SPEED 0.05f;

#define GOOMBA_BBOX_WIDTH 16
#define GOOMBA_BBOX_HEIGHT 15
#define GOOMBA_BBOX_HEIGHT_DIE 9

#define GOOMBA_STATE_WALKING 101
#define GOOMBA_STATE_DIE 202
#define GOOMBA_ANI_WALKING 0
#define GOOMBA_ANI_DIE 1

class CGoomBa : public CGameObject
{
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CGoomBa();
	virtual void SetState(int state);
};

