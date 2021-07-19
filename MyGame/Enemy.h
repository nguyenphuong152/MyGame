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

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;


public:
	CEnemy();
	~CEnemy();

	void SetLevel(int level) { this->level = level; };
	int GetLevel() { return this->level; };	

	void StartDie() { die = 1; die_start = GetTickCount64(); }
	void SetAttackedAnimation(AttackedBy obj, Points point);

	void ClearCoEvents();
	virtual void HandleCollision(vector<LPCOLLISIONEVENT> coEventRe) = 0;

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void SetState(int state);
};