#pragma once

#include "Enemy.h"
#include "Mario.h"
#include "GoomBa.h"

#define KOOPA_SHELL_VELOCITY_X	0.4f
#define KOOPA_WALKING_SPEED		0.03f
#define KOOPA_GRAVITY			0.002f
#define KOOPA_DEFLECT_SPEED		0.6f

#define KOOPA_BBOX_WIDTH		52
#define KOOPA_BBOX_HEIGHT		82
#define KOOPA_BBOX_HEIGHT_DIE	46

#define VALUE_ADJUST_SHELL		28
#define KOOPA_DIE_TIME			4000
#define KOOPA_RECOVER_TIME		2000

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
	ULONGLONG _recoverStart;

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
	
	void HandleCollision(vector<LPGAMEOBJECT>* coObjects);
	void ChangeDirection();
	void WalkThrough();

	void ResetRecover() { recover = 0; _recoverStart = 0; };
public:
	CKoopas();
	bool isHolded;
	
	void StartRecover() { recover = 1; _recoverStart = GetTickCount64(); }
	void LevelDown();
	void SetStateWhenPlayerJumpOn();
	virtual void SetState(int state);
	void UpdateShellPosition();

	void AttackedByTail();
};

