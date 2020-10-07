#pragma once
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

//thu tu theo ani add trong file txt
#define MARIO_ANI_SMALL_IDLE	0
#define MARIO_ANI_SMALL_WALKING	1
#define MARIO_ANI_SMALL_JUMP	2
#define MARIO_ANI_SMALL_STOP	3
#define MARIO_ANI_DIE			4
#define MARIO_ANI_BIG_IDLE		5
#define MARIO_ANI_BIG_WALKING	6
#define MARIO_ANI_BIG_JUMP		7
#define MARIO_ANI_BIG_STOP		8


#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 27

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000

class CMario : public CGameObject
{
	int untouchable;
	DWORD untouchable_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

public:
	int level;
	bool isOnGround = false;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void SetState(int state);
	void SetLevel(int l) { level = l; }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }

	void Reset();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	//Kiem tra collision voi item
	void CheckCollisionWithItems(vector<LPGAMEOBJECT>* listItem);
};


