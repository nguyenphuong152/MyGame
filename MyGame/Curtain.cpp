#include "Curtain.h"
#include "Utils.h"

CCurtain::CCurtain()
{
	SetObjectAnimation(CURTAIN_ANI);
	isEnable = true;
	isShowing = false;
	showcase = false;
	SetState(CURTAIN_STATE_LONG);
}

void CCurtain::Render()
{
	int ani = -1;
	if (state == CURTAIN_STATE_LONG) ani = LONG_CURTAIN;
	else if (state == CURTAIN_STATE_SUPER_BROS) ani = SUPER_BROS;
	else if (state == CURTAIN_STATE_THREE) ani = THREE;
	else ani = SHORT_CURTAIN;

	animation_set->at(ani)->Render(-1, 1, x, y);
}

void CCurtain::Update(DWORD dt, vector<LPGAMEOBJECT>* colObjects)
{
	CGameObject::Update(dt);
	if(state == CURTAIN_STATE_LONG)vy = -CURTAIN_SPEED;

	if (y < -500) {
		y = -500;
		vy = 0;
		SetState(CURTAIN_STATE_SHORT);
	}

	if (isShowing && state == CURTAIN_STATE_SUPER_BROS) {
		vy = CURTAIN_SPEED;
		if (y > 0) vy = 0;
	}

	if (isShowing && state == CURTAIN_STATE_THREE)
	{
		vy = CURTAIN_SPEED;
		if (y > 270) {
			showcase = true;
			vy = 0;
		}
	}



	y += dy;
}

void CCurtain::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

