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

		float min_tx, min_ty, nx = 0, ny;
		float rdx = 0, rdy = 0;
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		//day object ra mot khoang de k bi chong va cham
		
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;
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