#include "BreakableBrick.h"
#include "Utils.h"
#include "Brick.h"
#include "EffectPool.h"

CBreakableBrick::CBreakableBrick(float x, float y)
{
	isEnable = true;
	SetAnimation(BREAKABLE_BRICK_ANI);
	SetState(BREAKABLE_BRICK_VISUAL_STATE);
	SetPosition(x, y);
}

void CBreakableBrick::SetState(int state)
{
	CGameObject::SetState(state);
}

void CBreakableBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);
	if (CMario::GetInstance()->isJumpOnSwitch)
	{
		SetState(BREAKABLE_BRICK_COIN_STATE);
	}
}


void CBreakableBrick::Render()
{
	int ani = -1;
	if (state == BREAKABLE_BRICK_VISUAL_STATE)
		ani = BREAKABLE_BRICK_VISUAL_ANI;
	else
		ani = BREAKABLE_BRICK_COIN_ANI;
	animation_set->at(ani)->Render(1, x, y);
	//RenderBoundingBox();
}

void CBreakableBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BREAKABLE_BRICK_BBOX_WIDTH;
	b = y + BREAKABLE_BRICK_BBOX_WIDTH;
}

void CBreakableBrick::SetAttackedAnimation()
{
	CEffect* effect_1 = CEffectPool::GetInstance()->Create();
	CEffect* effect_2 = CEffectPool::GetInstance()->Create();
	CEffect* effect_3 = CEffectPool::GetInstance()->Create();
	CEffect* effect_4 = CEffectPool::GetInstance()->Create();

	if (effect_1 != NULL&&effect_2!=NULL&&effect_3!=NULL&&effect_4!=NULL)
	{
		effect_1->SetEffect(EffectName::debris, this,-1,-1);
		effect_2->SetEffect(EffectName::debris, this, -1, 1);
		effect_3->SetEffect(EffectName::debris, this, 1, -1);
		effect_4->SetEffect(EffectName::debris, this, 1, 1);
	}
}