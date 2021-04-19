#pragma once

#include "GameObject.h"
#include "Mario.h"

#define KOOPA_SHELL_VELOCITY_X	0.5f
#define KOOPA_WALKING_SPEED		0.1f
#define KOOPA_GRAVITY			0.0015f

#define KOOPA_BBOX_WIDTH		52
#define KOOPA_BBOX_HEIGHT		84
#define KOOPA_BBOX_HEIGHT_DIE	50

#define VALUE_ADJUST_SHELL		28
#define KOOPA_DIE_TIME			5000
#define KOOPA_RECOVER_TIME		1000

#define KOOPA_STATE_WALKING				100
#define KOOPA_STATE_DIE					200
#define KOOPA_STATE_DIE_WITH_VELOCITY	300
#define KOOPA_STATE_RECOVER				400

#define KOOPA_ANI						70
#define KOOPA_ANI_WALKING				0
#define KOOPA_ANI_DIE					1
#define KOOPA_ANI_DIE_WITH_VELOCITY		2
#define KOOPA_ANI_RECOVER				3

class CKoopas : public CGameObject
{

	CMario* player;
	int die;
	int recover;
	DWORD _dieStart;
	DWORD _recoverStart;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	bool isHolded = false;
	void StartDie() { die = 1; _dieStart = GetTickCount64(); };
	void StartRecover() { recover = 1; _recoverStart = GetTickCount64(); }
	CKoopas();
	virtual void SetState(int state);
	void SetAnimation();
	void UpdateShellPosition();
};

