#include "Brick.h"
#include "Utils.h"
#include "Mario.h"
#include "Items.h"
#include "Coin.h"
#include "PowerUp.h"
#include "One-upMushroom.h"

CBrick::CBrick(CGameObject* item,float y)
{
	this->item = item;
	SetAnimation(BRICK_ANI);
	isEnable = true;
	SetState(BRICK_STATE_UNTOUCH);
	oldY = y;
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
		if (dynamic_cast<CCoin*>(item))
		{
			CCoin* coin = dynamic_cast<CCoin*>(item);
			coin->SetState(COIN_STATE_JUMPING);
		}
		else if (dynamic_cast<CPowerUp*>(item))
		{
			CPowerUp* powerup = dynamic_cast<CPowerUp*>(item);
			powerup->DefinePowerUpType();
			powerup->SetState(POWERUP_STATE_GO_UP);
		}
		else if (dynamic_cast<COneUpMushroom*>(item))
		{
			COneUpMushroom* oneup_mushroom = dynamic_cast<COneUpMushroom*>(item);
			oneup_mushroom->SetState(ONE_UP_MUSHROOM_STATE_GO_UP);
		}

	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		CGameObject::Update(dt, coObjects);
		 if (state == BRICK_STATE_TOUCHED)
		 {
			vy += 0.00015*dt;
			if (y >= oldY)
			{
				y = oldY;
				vy = 0;
			}
			
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


