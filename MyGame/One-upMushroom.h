#pragma once
#include "GameObject.h"
#include "Mario.h"

#define ONE_UP_MUSHROOM_ANI				0

#define ONE_UP_MUSHROOM_STATE_GO_UP	        100
#define ONE_UP_MUSHROOM_STATE_WALKING		200

class COneUpMushroom :public CGameObject {
	//bool isActive;
	float start_y;
	CMario* player;
public:
	COneUpMushroom(float x,float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};