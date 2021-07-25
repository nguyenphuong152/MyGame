#pragma once
#include "GoomBa.h"

#define BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR	500
#define BROWN_PARA_GOOMBA_STATE_DROP			600
#define BROWN_PARA_GOOMBA_STATE_FLY			700

#define BROWN_PARA_GOOMBA_ANI_FLY					0
#define BROWN_PARA_GOOMBA_ANI_WALKING				1
#define BROWN_PARA_GOOMBA_ANI_GOOMBA				2
#define BROWN_PARA_GOOMBA_ANI_DIE					3

#define BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY			75
#define BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING		60

#define MAX_DISTANCE_TOP    300
#define MAX_DISTANCE_LEFT	6000
#define MAX_DISTANCE_RIGHT	6400

#define BROWN_PARA_GOOMBA_WALKING_TIME			7000
#define SPAWNING_TIME	2000

#define BROWN_PARA_GOOMBA_SHORT_JUMP_VELOCITY_Y				0.0001f
#define BROWN_PARA_GOOMBA_HIGH_JUMP_VELOCITY_Y				0.9f



class CBrownParaGoomba :public CGoomBa {

	ULONGLONG walking_start;
	int walking;
	ULONGLONG spawning_start;
	int spawning;

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
	void ResetWalking() { walking = 0; walking_start = 0; }

	void StartSpawning() { spawning = 1; spawning_start = GetTickCount64(); }
	void ResetSpawning() { spawning = 0; spawning_start = 0; }
};