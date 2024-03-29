#include "Coin.h"
#include "Utils.h"
#include "Brick.h"
#include "Grid.h"
#include "EffectPool.h"
#include "Game.h"

CCoin::CCoin(CoinType type, float x, float y)
{
	jump_start = 0;
	jumping = 0;
	this->type = type;
	SetObjectAnimation(COIN_ANI);
	SetPosition(x, y);
	isEnable = true;
	isActive = false;
	if (type == CoinType::spinning_coin) isActive = true;
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	if (state==COIN_STATE_JUMPING)
	{
		if (type == CoinType::jumping_coin || type == CoinType::short_jumping_coin)
		{
			isActive = true;
			vy = -COIN_DEFLECT_SPEED;
			StartJumping();
		}
	}
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		//
		CGameObject::Update(dt, coObjects);

		if (state == COIN_STATE_JUMPING) {
			if (type == CoinType::jumping_coin || type == CoinType::short_jumping_coin)
			vy += COIN_GRAVITY * dt;
		}
		y += dy;

		if (type == CoinType::jumping_coin)
		{
			if (jumping == 1 && GetTickCount64() - jump_start > JUMPING_TIME)
				FinishJumping();
		}
		else if (type == CoinType::short_jumping_coin)
		{
			if (jumping == 1 && GetTickCount64() - jump_start > JUMPING_TIME / 2)
				FinishJumping();
		}
	}
}


void CCoin::Render()
{
	int ani = -1;
	if (type == CoinType::spinning_coin)
		ani = COIN_ANI_SPINNING;
	else
		ani = COIN_ANI_JUMPING;
	if (isActive)
		animation_set->at(ani)->Render(1, 1, x, y);
	//RenderBoundingBox();
}

void CCoin::FinishJumping()
{
	ResetJumping();
	SetEffect(Points::POINT_100);
	isEnable = false;
	isActive = false;
}

void CCoin::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x+1;
	t = y+1;
	r = x + COIN_BBOX_WIDTH;
	b = y + COIN_BBOX_HEIGHT;
}

void CCoin::SetEffect(Points point)
{
	CEffect* effect = CEffectPool::GetInstance()->Create();
	if (effect != NULL)
	{
		effect->SetEffect(EffectName::point, this, 1, 1, point);
	}

	int p = 0;
	switch (point)
	{
	case Points::NONE:
		break;
	case Points::POINT_100:
		p = 100;
		break;
	case Points::POINT_200:
		p = 200;
		break;
	case Points::POINT_300:
		p = 300;
		break;
	}

	CMario* mario = CGame::GetInstance()->GetPlayer();
	mario->SetPoints(p);
	mario->SetCoins();
}