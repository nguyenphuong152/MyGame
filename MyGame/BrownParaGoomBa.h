#pragma once
#include "GoomBa.h"

#define BROWN_PARA_GOOMBA_STATE_FLY				100
#define BROWN_PARA_GOOMBA_STATE_WALKING			200
#define BROWN_PARA_GOOMBA_STATE_GOOMBA			300
#define BROWN_PARA_GOOMBA_STATE_DIE				400
#define BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR	500
#define BROWN_PARA_GOOMBA_STATE_DROP			600

#define BROWN_PARA_GOOMBA_ANI_FLY					0
#define BROWN_PARA_GOOMBA_ANI_WALKING				1
#define BROWN_PARA_GOOMBA_ANI_GOOMBA				2
#define BROWN_PARA_GOOMBA_ANI_DIE					3

#define BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY			75
#define BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING		62

#define MAX_DISTANCE_TOP 700
#define MAX_DISTANCE_LEFT	6000
#define MAX_DISTANCE_RIGHT	6400

#define BROWN_PARA_GOOMBA_WALKING_TIME			5000
#define SPAWNING_TIME	350

#define SHORT_JUMP_VELOCITY_Y				0.25f
#define HIGH_JUMP_VELOCITY_Y				0.6f



class CBrownParaGoomba :public CGoomBa {

	DWORD walking_start;
	int walking;
	DWORD spawning_start;
	int spawning;
	bool isOnGround;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();

	void CheckGoombaMoving();
	void ChangeStateWhenOverWalkingTime();

public:
	CBrownParaGoomba();
	virtual void SetState(int state);

	void SpawnMiniGoomba();

	void StartWalking() { walking = 1; walking_start = GetTickCount64(); }
	void ResetWalking() { walking = walking_start = 0; }

	void StartSpawning() { spawning = 1; spawning_start = GetTickCount64(); }
	void ResetSpawning() { spawning = spawning_start = 0; }
};