#include "Brick.h"
#include "Utils.h"
#include "Mario.h"
#include "Coin.h"
#include "PowerUp.h"
#include "One-upMushroom.h"
#include "Switch.h"
#include "Effect.h"
#include "EffectPool.h"

CBrick::CBrick(CGameObject* item, float y, BrickType type)
{
	coinCounts = 0;
	this->item = item;
	InitBrick(y,type);
}

CBrick::CBrick(float y, BrickType type)
{
	this->item = NULL;
	InitBrick(y,type);
}

void CBrick::InitBrick(float y, BrickType type)
{
	this->type = type;
	if (type == BrickType::question_brick)
	{
		SetObjectAnimation(BRICK_ANI);
	}
	else SetObjectAnimation(TWINKLE_BRICK_ANI);

	isEnable = true;
	SetState(BRICK_STATE_UNTOUCH);
	oldY = y;
	isTouch = false;
}

void CBrick::HandleBrickHasTenCoins()
{

	if (type == BrickType::twinkle_brick_coin && coinCounts < NUMBER_OF_COINS && isTouch == true) {
		if (dynamic_cast<CCoin*>(coins[coinCounts]))
		{
			CCoin* coin = dynamic_cast<CCoin*>(coins[coinCounts]);
			coin->SetState(COIN_STATE_JUMPING);
		}
		IncreaseCoinCounts();
		isTouch = false;
	}
}

void CBrick::AddCoins(CGameObject* coin)
{
	coins.push_back(coin);
}

void CBrick::DisableBrick()
{
	isEnable = false;
	if (item)  item->isEnable = false;

	SetAttackedAnimation();
}

void CBrick::Render()
{
	int ani = -1;
	if (state == BRICK_STATE_UNTOUCH || type == BrickType::twinkle_brick_no_item || type == BrickType::twinkle_brick_coin&&coinCounts<NUMBER_OF_COINS)
	{
		ani = BRICK_ANI_UNTOUCH;
	}
	else if (state == BRICK_STATE_TOUCHED||coinCounts>NUMBER_OF_COINS-1)
	{
		ani = BRICK_ANI_TOUCHED;
	}
	//RenderBoundingBox();
	animation_set->at(ani)->Render(-1,1, x, y);
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
		else if (dynamic_cast<CSwitch*>(item))
		{
			CSwitch* switch_item = dynamic_cast<CSwitch*>(item);
			switch_item->SetState(SWITCH_STATE_UNTOUCH);
		}
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	HandleBrickHasTenCoins();

	if (state == BRICK_STATE_TOUCHED)
	{
		vy += BRICK_DROP_VELOCITY_Y*dt;
		y += dy;
	}
	if (y >= oldY)
	{
		y = oldY;
		vy = 0;
		if (type == BrickType::twinkle_brick_coin && state==BRICK_STATE_TOUCHED && coinCounts<NUMBER_OF_COINS || type==BrickType::twinkle_brick_no_item && state == BRICK_STATE_TOUCHED)
		{
				SetState(BRICK_STATE_UNTOUCH);
		}
	}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_WIDTH;
}

void CBrick::SetAttackedAnimation()
{
	CEffect* effect_1 = CEffectPool::GetInstance()->Create();
	CEffect* effect_2 = CEffectPool::GetInstance()->Create();
	CEffect* effect_3 = CEffectPool::GetInstance()->Create();
	CEffect* effect_4 = CEffectPool::GetInstance()->Create();

	if (effect_1 != NULL && effect_2 != NULL && effect_3 != NULL && effect_4 != NULL)
	{
		effect_1->SetEffect(EffectName::debris, this, -1, -1, Points::NONE);
		effect_2->SetEffect(EffectName::debris, this, -1, 1, Points::NONE);
		effect_3->SetEffect(EffectName::debris, this, 1, -1, Points::NONE);
		effect_4->SetEffect(EffectName::debris, this, 1, 1, Points::NONE);
	}

	isEnable = false;
}
