#pragma once
#include "GameObject.h"

#define MARIO_WALKING_SPEED		0.15f 
//0.1f
#define MARIO_JUMP_SPEED_Y		0.5f
#define MARIO_JUMP_DEFLECT_SPEED 0.2f
#define MARIO_GRAVITY			0.002f
#define MARIO_DIE_DEFLECT_SPEED	 0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING         100
#define MARIO_STATE_JUMP			200
#define MARIO_STATE_DIE				300


//thu tu theo ani add trong file txt
#define MARIO_ANI_SMALL_IDLE	0
#define MARIO_ANI_SMALL_WALKING	1
#define MARIO_ANI_JUMP			2
#define MARIO_ANI_DIE			3

#define MARIO_ANI_DIE				8

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

class CMario : public CGameObject
{
	int level;
	int untouchable;
	DWORD untouchable_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

public:
	bool isJumping = false;



	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();
	void Jumping();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};


