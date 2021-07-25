#pragma once
#include "GameObject.h"
#include "EffectPool.h"
enum class AttackedBy
{
	Tail,
	Mario,
	KoopaShell
};

class CEnemy :public CGameObject
{
protected:
	ULONGLONG die_start;
	int level;
	int die;

	CMario* player;
public:
	CEnemy();
	~CEnemy();

	void SetLevel(int level) { this->level = level; };
	int GetLevel() { return this->level; };	

	void StartDie() { die = 1; die_start = GetTickCount64(); }
	void SetAttackedAnimation(AttackedBy obj, Points point);
	virtual void HandleCollision(vector<LPGAMEOBJECT>* coObjects) = 0;

	virtual void Update(DWORD dt);
	virtual void SetState(int state);
};