#include "Enemy.h"
#include "Game.h"
#include "RedVenusFireTrap.h"
#include "Koopas.h"


CEnemy::CEnemy()
{
	isEnable = true;
	player = CGame::GetInstance()->GetPlayer();
}

CEnemy::~CEnemy()
{

}

void CEnemy::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CGameObject::Update(dt, colObject);

	coEventsResult.clear();
	coEvents.clear();

	CalcPotentialCollisions(colObject, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult,nx,ny);
	}

}

void CEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}

void CEnemy::SetAttackedAnimation(AttackedBy obj,Points point)
{
	CEffect* effect = CEffectPool::GetInstance()->Create();
	if (effect != NULL)
	{
		if (obj == AttackedBy::Tail)
		{
			effect->SetEffect(EffectName::attack_by_tail, this);
		}
		else if (obj == AttackedBy::Mario && point!=Points::NONE)
		{
			effect->SetEffect(EffectName::point, this, 1, 1, point);
		}
	}
}

void CEnemy::ClearCoEvents()
{
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

//void CEnemy::SetPlayerData(CMario& mario)
//{
//	player = &mario;
//}	