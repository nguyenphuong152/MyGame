#pragma once
#include "GameObject.h"

#define CURTAIN_ANI	60
#define LONG_CURTAIN	0
#define SHORT_CURTAIN	1	
#define SUPER_BROS		2
#define THREE			3

#define CURTAIN_STATE_LONG 100
#define CURTAIN_STATE_SHORT 200
#define CURTAIN_STATE_SUPER_BROS 300
#define CURTAIN_STATE_THREE		400

#define CURTAIN_SPEED 0.25f

class CCurtain : public CGameObject {
public:
	bool isShowing;
	bool showcase;
	CCurtain();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};