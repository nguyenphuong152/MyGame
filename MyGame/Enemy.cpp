#include "Enemy.h"
#include "Game.h"
#include "RedVenusFireTrap.h"
#include "Koopas.h"


CEnemy::CEnemy()
{
	level = 0;
	die = 0;
	die_start = 0;
	isEnable = true;
	player = CGame::GetInstance()->GetPlayer();
}

CEnemy::~CEnemy()
{

}

void CEnemy::Update(DWORD dt)
{
	//CGameObject::Update(dt);
}

void CEnemy::SetState(int state)
{
	CGameObject::SetState(state);
}

void CEnemy::SetAttackedAnimation(AttackedBy obj,Points point)
{
	CEffect* effect = CEffectPool::GetInstance()->Create();
	CEffect* effect1 = CEffectPool::GetInstance()->Create();
	if (effect != NULL && effect1 !=NULL)
	{
		if (obj == AttackedBy::Tail)
		{
			effect->SetEffect(EffectName::attack_by_tail, this);
			effect1->SetEffect(EffectName::point, this, 1, 1, point);
		}
		else if (obj == AttackedBy::Mario && point!=Points::NONE)
		{
			effect->SetEffect(EffectName::point, this, 1, 1, point);
		}
	}
	
	int p = 0;
	switch (point)
	{
	case Points::NONE:
		break;
	case Points::POINT_100:
		p = 100;
		break;
	case Points::POINT_200:
		p = 200;
		break;
	case Points::POINT_300:
		p = 300;
		break;
	}

	player->SetPoints(p);
	player->SetCoins();
}


//void CEnemy::SetPlayerData(CMario& mario)
//{
//	player = &mario;
//}	