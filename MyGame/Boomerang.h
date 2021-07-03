#pragma once
#include "GameObject.h"
#include "BoomerangBrother.h"

#define BOOMERANG_BBOX_WIDTH		48

#define BOOMERANG_VELOCITY_X			0.3f
#define BOOMERANG_VELOCITY_Y_NEAR	0.1f		


#define BOOMERANG_GRAVITY			0.0015f

class CBoomerang : public CGameObject
{
	friend class CBoomerangPool;
private:
	CBoomerang();
	union {
		struct
		{
			bool inUse;
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

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

