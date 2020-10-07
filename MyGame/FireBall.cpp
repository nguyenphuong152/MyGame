#include "FireBall.h"
#include "Utils.h"

CFireBall::CFireBall(CMario* player , bool isShootingUp)
{
	isEnable = true;
	SetPosition(FIREBALL_POSITION_X, FIREBALL_POSITION_Y);
	this->player = player;
	this->isShootingUp = isShootingUp;
	SetState(FIREBALL_STATE_FIRE);
}

void CFireBall::Render()
{
	if (isEnable)
	{
		animation_set->at(0)->Render(0, x, y);
	}
	//RenderBoundingBox();
}

void CFireBall::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {

	CGameObject::Update(dt, colObject);
	

	int dir = -1;
	if (isShootingUp) dir = 1;

	if (player->x > POSITION_CHANGE_VY) {
		DebugOut(L"x: %d \n", dir);
		vy = dir*FIREBALL_VELOCITY_Y_NEAR * vx;
		
	}
	else vy = dir* FIREBALL_VELOCITY_Y_FAR * vx;
	
	// check lại vx nếu k khi con này quay phải, vy sẽ bị ngược chiều
	if (vx > 0) vy = -vy;

	x += dx;
	y += dy;

	//DebugOut(L"y: %f \n", y);
	if (y < 232 || y>450) isEnable = false;
}

void CFireBall::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireBall::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == FIREBALL_STATE_FIRE)
	{
		if (player->x < POSITION_PIPE)
			vx = -FIREBALL_VELOCITY_X;
		else vx = FIREBALL_VELOCITY_X;
	}
}

