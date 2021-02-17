#pragma once

class CMarioState;

#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_ACCELERATION		0.0004f //giam lai con 0.0001f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING       100
#define MARIO_STATE_JUMP			200
#define MARIO_STATE_DIE			300
#define MARIO_STATE_STOP_DOING	400

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3


//thu tu theo ani add trong file txt
#define MARIO_ANI_SMALL_IDLE	0
#define MARIO_ANI_SMALL_WALKING	1
#define MARIO_ANI_SMALL_JUMP	2
#define MARIO_ANI_SMALL_RUN		3
#define MARIO_ANI_SMALL_PRE_FLY	4
#define MARIO_ANI_SMALL_FLY		5
#define MARIO_ANI_SMALL_STOP	6
#define MARIO_ANI_SMALL_KICK	7
#define MARIO_ANI_DIE			8
//big
#define MARIO_ANI_BIG_IDLE		9
#define MARIO_ANI_BIG_WALKING	10
#define MARIO_ANI_BIG_JUMP		11
#define MARIO_ANI_BIG_SIT		12
#define MARIO_ANI_BIG_RUN		13
#define MARIO_ANI_BIG_PRE_FLY	14
#define MARIO_ANI_BIG_FLY		15
#define MARIO_ANI_BIG_STOP		16
#define MARIO_ANI_BIG_KICK		17
//racoon
#define MARIO_ANI_RACOON_IDLE		18
#define MARIO_ANI_RACOON_WALKING	19
#define MARIO_ANI_RACOON_SIT		20
#define MARIO_ANI_RACOON_JUMP		21
#define MARIO_ANI_RACOON_RUN		22
#define MARIO_ANI_RACOON_DROP		23
#define MARIO_ANI_RACOON_PRE_FLY	24
#define MARIO_ANI_RACOON_FLY		25
#define MARIO_ANI_RACOON_STOP		26
#define MARIO_ANI_RACOON_SPIN		27
#define MARIO_ANI_RACOON_KICK		28

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 26
#define MARIO_BIG_BBOX_SIT_HEIGHT 17

#define MARIO_RACOON_BBOX_WIDTH  21
#define MARIO_RACOON_BBOX_HEIGHT 27
#define MARIO_RACOON_BBOX_SIT_HEIGHT 17

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

#define DIRECTION_LEFT_TO_RIGHT 1
#define DIRECTION_RIGHT_TO_LEFT -1

class CMario : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

public:
	CMarioState* marioState;
	int level;
	int animation;
	bool isOnGround = false;
	bool isSitting = false;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void InitState();
	void SetVelocityX(float velocity_x) {
		vx = velocity_x;
	}
	void SetVelocityY(float velocity_y) {
		vy = velocity_y;
	}
	void SetDirection(int dir) {
		nx = dir;
	}
	void ChangeState(CMarioState* new_state) {
		marioState = new_state;
	}

	void SetLevel(int l) { level = l; }
	void SetAnimation(int ani) { animation = ani; }
	int GetCurrentAnimation() { return animation; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	void TransformRacoon();
	void HandleInput();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	//Kiem tra collision voi item
	void CheckCollisionWithItems(vector<LPGAMEOBJECT>* listItem);

};


