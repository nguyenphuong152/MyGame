#pragma once
#include "GameObject.h"
#include "BrownParaGoomBa.h"

#define MINIGOOMBA_BBOX_WIDTH		32

#define MINIGOOMBA_VELOCITY_X		0.3f


#define MINIGOOMBA_TURNBACK_SPEED	0.01f

#define MINIGOOMBA_FLOATING_TIME	200
#define MINIGOOMBA_LIVING_TIME		960
#define MINIGOOMBA_GRAVITY			0.01f
#define MINIGOOMBA_SPINNING_VELOCITY_Y	0.18f

#define MINIGOOMBA_STATE_SURROUND_MARIO	100
#define MINIGOOMBA_STATE_NORMAL			200

class CMiniGoomba : public CGameObject
{
	friend class CMiniGoombaPool;
private:
	CMiniGoomba();
	union {
		struct
		{
			bool inUse;
			bool isSurroundMario;

			int changeDirection;
			int direction;
			ULONGLONG changeDirection_start;

			int alive;
			ULONGLONG alive_start;
		} live;
		//state when it's available
		CMiniGoomba* next;
	} _state;
public:
	CMiniGoomba* GetNext() {
		return _state.next;
	}
	void SetNext(CMiniGoomba* goomba) {
		_state.next = goomba;
	}
	bool FinishShooting();

	void StartChangeDirection() { _state.live.changeDirection = 1; _state.live.changeDirection_start = GetTickCount64(); }
	void ResetChangeDirection() { _state.live.changeDirection = 0; _state.live.changeDirection_start = 0; }

	void StartLiving() { _state.live.alive = 1; _state.live.alive_start = GetTickCount64(); }
	void ResetLive(){ _state.live.alive = _state.live.alive_start = 0; };

	void StartSpawning(CBrownParaGoomba* goomba);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

