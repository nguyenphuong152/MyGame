#pragma once

#include "Enemy.h"
#include "Mario.h"
#include "GoomBa.h"

#define KOOPA_SHELL_VELOCITY_X	0.8f
#define KOOPA_WALKING_SPEED		0.1f
#define KOOPA_GRAVITY			0.0015f
#define KOOPA_DEFLECT_SPEED		0.6f

#define KOOPA_BBOX_WIDTH		52
#define KOOPA_BBOX_HEIGHT		82
#define KOOPA_BBOX_HEIGHT_DIE	48

#define VALUE_ADJUST_SHELL		28
#define KOOPA_DIE_TIME			5000
#define KOOPA_RECOVER_TIME		1000

#define KOOPA_STATE_WALKING				100
#define KOOPA_STATE_DIE					200
#define KOOPA_STATE_DIE_WITH_VELOCITY	300
#define KOOPA_STATE_RECOVER				400

#define KOOPA_ANI_WALKING				0
#define KOOPA_ANI_DIE					1
#define KOOPA_ANI_DIE_WITH_VELOCITY		2
#define KOOPA_ANI_RECOVER				3

#define KOOPA_LEVEL_2	2
#define KOOPA_LEVEL_1	1

class CKoopas : public CEnemy
{
protected:
	int recover;
	DWORD _recoverStart;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	CKoopas();
	bool isHolded = false;
	bool isOnGround = false;
	
	void StartRecover() { recover = 1; _recoverStart = GetTickCount64(); }
	
	virtual void SetState(int state);
	void UpdateShellPosition();

	void AttackedByTail();
};

