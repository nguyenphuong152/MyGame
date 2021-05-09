#pragma once
#include "Mario.h"
#include "GameObject.h"

#define FIREBALL_EXPLOSE_FX		0
#define ATTACK_BY_TAIL_FX		1
#define DEBRIS_FX				2

#define ANIMATED_TIME			300

enum class EffectName {
	attack_by_tail,
	fireball_explose,
	debris
};

class CEffect : public CGameObject
{
	friend class CEffectPool;
private:
	CEffect();
	int ani;
	bool inUse = false;
	DWORD animated_start;

	union {
		//state when it's available
		CEffect* next;
	} _state;
public:
	CEffect* GetNext() {
		return _state.next;
	}
	void SetNext(CEffect* fireball) {
		_state.next = fireball;
	}

	bool FinishAnimated();
	void SetEffect(EffectName name, CGameObject* obj);
	void StartAnimated() { animated_start = GetTickCount64(); }

	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
	virtual void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

