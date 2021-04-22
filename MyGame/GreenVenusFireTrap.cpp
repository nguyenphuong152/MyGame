#include "GreenVenusFireTrap.h"
#include "Ground.h"
#include "FireBall.h"
#include "FireBallPool.h"


CGreenVenusFireTrap::CGreenVenusFireTrap()
{
	SetAnimation();
	isEnable = true;
	startShooting = -1;
	isShooting = false;
	isShootingUp = false;
	//SetState(VENUS_STATE_GO_UP);
}

void CGreenVenusFireTrap::Render()
{
	CRedVenusFireTrap::Render();
}

void CGreenVenusFireTrap::SetState(int state)
{
	CRedVenusFireTrap::SetState(state);
}

void CGreenVenusFireTrap::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (CMario::GetInstance()->x < POSITION_PIPE_X)  nx = -1;
	else nx = 1;

	CRedVenusFireTrap::Update(dt, coObjects);
}


void CGreenVenusFireTrap::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	CRedVenusFireTrap::GetBoundingBox(l, t, r, b);
}

void CGreenVenusFireTrap::CheckDirection()
{
	CRedVenusFireTrap::CheckDirection();
}

void CGreenVenusFireTrap::StartShooting()
{
	CRedVenusFireTrap::StartShooting();
}

void CGreenVenusFireTrap::SetAnimation()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(GREEN_VENUS_FIRETRAP_ANI);
	SetAnimationSet(ani_set);
}
