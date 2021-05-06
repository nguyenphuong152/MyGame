﻿#include "Brick.h"
#include "Utils.h"
#include "Mario.h"
#include "Items.h"
#include "Coin.h"
#include "MushroomPowerUp.h"
#include "LeafPowerUp.h"

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
		else if (dynamic_cast<CMushroomPowerUp*>(item))
		{
			CMushroomPowerUp* mushroom = dynamic_cast<CMushroomPowerUp*>(item);
			mushroom->SetState(MUSHROOM_STATE_GO_UP);
		}
		else if (dynamic_cast<CLeafPowerUp*>(item))
		{
			CLeafPowerUp* leaf = dynamic_cast<CLeafPowerUp*>(item);
			leaf->SetState(LEAF_STATE_GO_UP);
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


