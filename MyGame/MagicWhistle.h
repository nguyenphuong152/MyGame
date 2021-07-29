#pragma once
#include "GameObject.h"

#define MAGIC_WHISTLE_STATE_INACTIVE	100
#define MAGIC_WHISTLE_STATE_ACTIVE		200

#define MAGIC_WHISTLE_SPEED 0.1f
#define MAGIC_WHISTLE_APPEARED_TIME	800

#define MAGIC_WHISTLE_ANI	51

class CMagicWhistle :public CGameObject
{
	ULONGLONG active_star;
	void StartActive() { active_star = GetTickCount64(); };
public:
	CMagicWhistle();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
