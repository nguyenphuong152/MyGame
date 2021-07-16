#pragma once
#include "GameObject.h"

#define CARD_RANDOM			0
#define MUSHROOM_CARD		1
#define STAR_CARD			2
#define	WHITE_FLOWER_CARD	3

#define CARD_BBOX			58

#define CARD_STATE_UNTOUCH	100
#define CARD_STATE_TOUCH	200

#define CARD_ANIMATED_TIME	    1500

#define CARD_VELOCITY_Y		0.5f
#define CARD_GRAVITY	    0.00015f

class CCard : public CGameObject {
private:
	ULONGLONG animated_start;
	int numbAni = 1;
public:
	CCard();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);

	void StartAnimated() { animated_start = GetTickCount64(); }
};