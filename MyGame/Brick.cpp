#include "Brick.h"
#include "Utils.h"
#include "Mario.h"
#include "Items.h"

CBrick::CBrick()
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(BRICK_ANI);
	SetAnimationSet(ani_set);

	isEnable = true;
	SetState(BRICK_STATE_UNTOUCH);
}

void CBrick::Render()
{
	int ani = -1;
	if (state == BRICK_STATE_UNTOUCH)
	{
		ani = BRICK_ANI_UNTOUCH;
	}
	else if (state == BRICK_STATE_TOUCHED)
	{
		ani = BRICK_ANI_TOUCHED;
	}
	animation_set->at(ani)->Render(0, x, y);
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == BRICK_STATE_TOUCHED)
	{
		vy = -BRICK_VELOCITY_Y;
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

		CGameObject::Update(dt, coObjects);
		if (state == BRICK_STATE_UNTOUCH)
		{
			oldY = y;
		}
		else if (y < oldY && vy <0)
		{
			vy = BRICK_DROP_VELOCITY_Y;
		}
		else if (vy==BRICK_DROP_VELOCITY_Y&&y>=oldY) {
			y = oldY;
			vy = 0;
		}

		y += dy;
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}


