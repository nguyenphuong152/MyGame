#include "EffectPool.h"
#include "Utils.h"


CEffect::CEffect()
{
	inUse = false;
	ani = -1;
	animated_start = 0;
}

void CEffect::SetEffect(EffectName name, CGameObject* obj)
{
	if (obj != NULL)
	{
		isEnable = true;
		inUse = true;

		SetPosition(obj->x, obj->y);
		StartAnimated();

		switch (name)
		{
		case EffectName::attack_by_tail:
			ani = ATTACK_BY_TAIL_FX;
			break;
		case EffectName::fireball_explose:
			ani = FIREBALL_EXPLOSE_FX;
			break;
		case EffectName::debris:
			ani = DEBRIS_FX;
			break;
		}
	}
}

void CEffect::Render()
{
	if (ani!= -1)
	{
		animation_set->at(ani)->Render(0, x, y);
	}
	//RenderBoundingBox();
}


void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {

	CGameObject::Update(dt, colObject);
	if (inUse && GetTickCount64() - animated_start > ANIMATED_TIME)
	{
		isEnable = false;
		animated_start = 0;
	}
}

void CEffect::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = 0;
	b = 0;
}

void CEffect::SetState(int state)
{
	CGameObject::SetState(state);
}

bool CEffect::FinishAnimated()
{
	if (!isEnable&& inUse)
	{
		inUse = false;
		return true;
	}
	else return false;
}

