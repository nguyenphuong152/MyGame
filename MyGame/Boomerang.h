#pragma once
#include "GameObject.h"
#include "BoomerangBrother.h"

#define BOOMERANG_BBOX_WIDTH		54
#define MAX_DISTANCE	350

#define BOOMERANG_VELOCITY_X		0.5f
#define BOOMERANG_VELOCITY_Y		0.3f

#define BOOMERANG_TURNBACK_SPEED	0.01f


#define BOOMERANG_GRAVITY			0.01f

class CBoomerang : public CGameObject
{
	friend class CBoomerangPool;
private:
	CBoomerang();
	union {
		struct
		{
			CBoomerangBrother* bBrother;
			bool inUse;
			bool changeDirection;
			float start_x;
		} live;
		//state when it's available
		CBoomerang* next;
	} _state;
public:
	CBoomerang* GetNext() {
		return _state.next;
	}
	void SetNext(CBoomerang* BOOMERANG) {
		_state.next = BOOMERANG;
	}
	bool FinishShooting();

	void StartThrowing(CBoomerangBrother* bBrother);
	void SetBoomerangBrother(CBoomerangBrother* bBrother) {
		_state.live.bBrother = bBrother;
	}

	void DisableBoomerang();
	void DisableBoomerangByCamera();
	void ChangeBoomerangDirection();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

