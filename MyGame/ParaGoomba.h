#pragma once
#include "GoomBa.h"

#define PARA_GOOMBA_STATE_FLY				400


#define PARA_GOOMBA_ANI_FLY					0
#define PARA_GOOMBA_ANI_WALKING				1
#define PARA_GOOMBA_ANI_GOOMBA				2
#define PARA_GOOMBA_ANI_DIE					3

#define PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY			75
#define PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING		63

#define JUMPING_TIMES_BEFORE_HIGH_JUMP		2
#define PARA_GOOMBA_WALKING_TIME			800

#define PARA_GOOMBA_SHORT_JUMP_VELOCITY_Y				0.25f
#define PARA_GOOMBA_HIGH_JUMP_VELOCITY_Y				0.35f



class CParaGoomba :public CGoomBa {

	ULONGLONG walking_start;
	int walking;
	int jumpingTimes;
	
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CParaGoomba();
	virtual void SetState(int state);
	void StartWalking() { walking = 1; walking_start = GetTickCount64(); }
};