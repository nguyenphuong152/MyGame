#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "Utils.h"

#define FIREBALL_BBOX_WIDTH		15
#define FIREBALL_BBOX_HEIGHT	15

#define FIREBALL_VELOCITY_X			0.3f
#define FIREBALL_VELOCITY_Y_NEAR	0.1f
#define FIREBALL_VELOCITY_Y_FAR		0.4f
#define FIREBALL_DEFLECT_Y			0.45f

#define FIREBALL_GRAVITY			0.0015f

#define FIREBALL_ANI				62

#define FIREBALL_STATE_EXPLOSIVE	100

#define RANGE_X_LEFT	287
#define RANGE_X_RIGHT	400

class CFireball : public CGameObject
{
	friend class CFireBallPool;
private:
	CFireball();
	bool isShootingUp;
	bool inUse = false;

	CMario* player;
	union {
		//state when it's available
		CFireball* next;
	} _state;
public:
	CFireball* GetNext()  { 
		return _state.next; 
	}
	void SetNext(CFireball* fireball) {
		_state.next = fireball;
	}

	bool FinishShooting();

	void Init(float x, float y,bool isShootingUp, CMario* mario);
	void DisableFireballByCamera(vector<LPGAMEOBJECT>* listObject);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

