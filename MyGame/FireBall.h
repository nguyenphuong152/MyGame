#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Utils.h"

#define FIREBALL_BBOX_WIDTH 14
#define FIREBALL_BBOX_HEIGHT 14

#define FIREBALL_STATE_FIRE 0
#define FIREBALL_VELOCITY_X 0.05f

#define FIREBALL_ANI 62

#define FIREBALL_VELOCITY_Y_NEAR 0.8f
#define FIREBALL_VELOCITY_Y_FAR 0.4f

#define RANGE_X_LEFT 287
#define RANGE_X_RIGHT 400

class CFireballTest : public CGameObject
{
	friend class CFireBallPool;
private:
	CFireballTest();
	bool isShootingUp;
	CMario* player;
	union {
		//state when it's available
		CFireballTest* next;
	} _state;
public:
	CFireballTest* GetNext()  { 
		return _state.next; 
	}
	void SetNext(CFireballTest* fireball) {
		_state.next = fireball;
	}

	void Init(float x, float y,CMario* player,bool isShootingUp);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

