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
		effect = name;

		switch (name)
		{
		case EffectName::attack_by_tail:
			ani = ATTACK_BY_TAIL_FX;
			break;
		case EffectName::fireball_explose:
			ani = FIREBALL_EXPLOSE_FX;
			break;
		}

		SetPosition(obj->x, obj->y);
		StartAnimated();
	}
}

void CEffect::SetEffect(EffectName name, CGameObject* obj, int nx_direction,int ny_direction,Points point)
{
	if (obj != NULL)
	{
		isEnable = true;
		inUse = true;
		effect = name;

		if(name == EffectName::debris)
		{
			ani = DEBRIS_FX;
			vy = DEBRIS_VELOCITY_Y * ny_direction;
			vx = DEBRIS_VELOCITY_X * nx_direction;
		}
		else if (name == EffectName::point && point!=Points::NONE)
		{
			if (point == Points::POINT_100)   ani = P_100;
			else if (point == Points::POINT_200)  ani = P_200;
			else ani = P_300;

			vy = -DEBRIS_VELOCITY_Y;
		}
		
		SetPosition(obj->x, obj->y - 10);
		StartAnimated();
	}
}



void CEffect::Render()
{
	if (ani!= -1)
	{
		animation_set->at(ani)->Render(-1,1, x, y);
	}
		
	//RenderBoundingBox();
}


void CEffect::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	colObject->push_back(this);
	CGameObject::Update(dt, colObject);

	if (effect == EffectName::debris||effect ==EffectName::point)
	{
		vy += 0.0015 * dt;
		if (vy > 0 && effect == EffectName::debris) {
			vy = 0.2f;
		}

		x += dx;
		y += dy;
	}
	
	if (effect == EffectName::debris)
	{
		DisableEffect(ANIMATED_TIME * 3);
	}
	else {
		DisableEffect(ANIMATED_TIME );
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

void CEffect::DisableEffect(int time)
{
	if (inUse && GetTickCount64() - animated_start > time)
	{
		isEnable = false;
		animated_start = 0;
	}
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

