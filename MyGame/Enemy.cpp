#include "Enemy.h"
#include "Game.h"


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

//void CEnemy::SetPlayerData(CMario& mario)
//{
//	player = &mario;
//}	