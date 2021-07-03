#pragma once
#include "Mario.h"
#include "GameObject.h"

#define FIREBALL_EXPLOSE_FX		0
#define ATTACK_BY_TAIL_FX		1
#define DEBRIS_FX				2
#define P_100					3
#define P_200					4
#define P_300					5

#define ANIMATED_TIME			300
#define DEBRIS_VELOCITY_X		0.1f
#define DEBRIS_VELOCITY_Y		0.5f

enum class EffectName {
	attack_by_tail,
	fireball_explose,
	debris,
	point,
};

enum class Points {
	NONE,
	POINT_100,
	POINT_200,
	POINT_300
};

class CEffect : public CGameObject
{
	friend class CEffectPool;
private:
	CEffect();
	EffectName effect;
	int ani;
	bool inUse = false;
	DWORD animated_start;

	
	//state when it's available
	CEffect* next;
public:
	CEffect* GetNext() {
		return next;
	}
	void SetNext(CEffect* effect) { 
		next = effect;
	}

	bool FinishAnimated();
	void SetEffect(EffectName name, CGameObject* obj);
	void SetEffect(EffectName name,CGameObject* obj, int nx, int ny, Points points);
	void StartAnimated() { animated_start = GetTickCount64(); }
	void DisableEffect(int time);

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

