#pragma once
#include "GameObject.h"
#include "EffectPool.h"
enum class AttackedBy
{
	Tail,
	Mario
};

class CEnemy :public CGameObject
{
protected:
	DWORD die_start;
	int level;
	int die;

	CMario* player;

public:
	CEnemy();
	~CEnemy();

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void SetState(int state);

	void SetLevel(int level) { this->level = level; };
	int GetLevel() { return this->level; };

	void StartDie() { die = 1; die_start = GetTickCount64(); }
	void SetAttackedAnimation(AttackedBy obj,Points point);
	void SetPlayerData(CMario& mario);
};