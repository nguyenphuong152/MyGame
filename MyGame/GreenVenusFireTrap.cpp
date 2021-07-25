#include "GreenVenusFireTrap.h"
#include "Ground.h"
#include "FireBall.h"
#include "FireBallPool.h"


CGreenVenusFireTrap::CGreenVenusFireTrap()
{
	startShooting = -1;
	isShooting = false;
	isShootingUp = false;
	SetState(VENUS_STATE_GO_UP);
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
	CRedVenusFireTrap::CheckDirectionForRender(GREEN_POSITION_PIPE_X);

	CRedVenusFireTrap::HandleShooting(GREEN_POSITION_PIPE_Y, GREEN_VENUS_BBOX_HEIGHT);

	if (GetTickCount64() - changeState_start > GREEN_VENUS_MOVING_TIME && changeState == 1)
	{
		ResetChangeState();
		SetState(VENUS_STATE_GO_DOWN);
	}
	
	HandleShooting(POSITION_PIPE_Y, VENUS_BBOX_HEIGHT);
	
	CGameObject::Update(dt);
	
	HandleCollision(coObjects);

}


void CGreenVenusFireTrap::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	CRedVenusFireTrap::HandleCollision(coObjects);
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

