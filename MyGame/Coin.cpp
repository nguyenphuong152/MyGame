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
	if (type == CoinType::spinning_coin) isActive = true;
}

void CCoin::SetState(int state)
{
	CGameObject::SetState(state);
	if (type == CoinType::jumping_coin&&state==COIN_STATE_JUMPING)
	{
		isActive = true;
		vy = -COIN_DEFLECT_SPEED;
		StartJumping();
	}
}

void CCoin::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (isActive)
	{
		//DebugOut(L"vooooo %d \n", dt);
		CGameObject::Update(dt, coObjects);

		if (jumping == 1 && GetTickCount64() - jump_start > JUMPING_TIME) {
			ResetJumping();
			SetEffect(Points::POINT_100);
			isEnable = false;
			isActive = false;
		}

		if (type == CoinType::jumping_coin && state == COIN_STATE_JUMPING) vy += COIN_GRAVITY * dt;
		y += dy;
	}
}


void CCoin::Render()
{
	int ani = -1;
	if (type == CoinType::jumping_coin)
		ani = COIN_ANI_JUMPING;
	else
		ani = COIN_ANI_SPINNING;
	if (isActive)
	{
		animation_set->at(ani)->Render(1, 1, x, y);
	}
	//RenderBoundingBox();
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