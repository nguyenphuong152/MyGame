#pragma once
#include "GoomBa.h"

#define PARA_GOOMBA_ANI 31

#define PARA_GOOMBA_STATE_FLY				100
#define PARA_GOOMBA_STATE_WALKING			200
#define PARA_GOOMBA_STATE_GOOMBA			300
#define PARA_GOOMBA_STATE_DIE				400

#define PARA_GOOMBA_ANI_FLY					0
#define PARA_GOOMBA_ANI_WALKING				1
#define PARA_GOOMBA_ANI_GOOMBA				2
#define PARA_GOOMBA_ANI_DIE					3

#define PARA_GOOMBA_LEVEL_2					2
#define PARA_GOOMBA_LEVEL_1					1

#define PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT		67

#define JUMPING_TIMES_BEFORE_HIGH_JUMP		2
#define PARA_GOOMBA_WALKING_TIME			500


class CParaGoomba :public CGoomBa {

	DWORD walking_start;
	int walking;
	int level;
	int jumpingTimes;
	bool isOnGround;
	
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CParaGoomba();
	virtual void SetState(int state);
	void SetLevel(int level) { this->level = level; };
	int GetLevel() { return this->level; };
	void StartWalking() { walking = 1; walking_start = GetTickCount64(); }
};