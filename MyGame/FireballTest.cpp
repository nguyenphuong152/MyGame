#include "FireballTest.h"
#include "RedVenusFireTrap.h"
#include "Utils.h"

CFireballTest::CFireballTest()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(FIREBALL_ANI);
	SetAnimationSet(ani_set);
	isShootingUp = false;
}

void CFireballTest::Init(float x, float y,CMario* player, bool isShootingUp)
{
	SetPosition(x, y);
	this->player = player;
	this->isShootingUp = isShootingUp;
	isEnable = true;
	SetState(FIREBALL_STATE_FIRE);
}

void CFireballTest::Render()
{
	if (state==FIREBALL_STATE_FIRE)
	{
		animation_set->at(0)->Render(0, x, y);
	}
	//RenderBoundingBox();
}


void CFireballTest::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {

	CGameObject::Update(dt, colObject);

	if (!isEnable) return;

	int dir = -1;
	if (isShootingUp) dir = 1;

	if (player->x > RANGE_X_LEFT&&player->x< RANGE_X_RIGHT) {
		vy = dir * FIREBALL_VELOCITY_Y_NEAR * vx;

	}
	else vy = dir * FIREBALL_VELOCITY_Y_FAR * vx;

	// check lại vx nếu k khi con này quay phải, vy sẽ bị ngược chiều
	if (vx > 0) vy = -vy;

	x += dx;
	y += dy;

	//DebugOut(L"y: %f \n", y);
	//hardcode
	if (y < 232 || y>450) isEnable = false;
}

void CFireballTest::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + FIREBALL_BBOX_WIDTH;
	b = t + FIREBALL_BBOX_HEIGHT;
}

void CFireballTest::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == FIREBALL_STATE_FIRE)
	{
		if (player->x < POSITION_PIPE)
			vx = -FIREBALL_VELOCITY_X;
		else 
			vx = FIREBALL_VELOCITY_X;
	}
}

