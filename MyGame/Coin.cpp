#include "Coin.h"
#include "Utils.h"
#include "Brick.h"
#include "Grid.h"

CCoin::CCoin(CoinType type, float x, float y)
{
	jump_start = 0;
	jumping = 0;
	this->type = type;
	SetAnimation(COIN_ANI);
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
			isEnable = false;
			isActive = false;
		}

		if (type == CoinType::jumping_coin && state == COIN_STATE_JUMPING) vy += COIN_GRAVITY * dt;

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		//if no collision occured, proceed normally
		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float nx = 0, ny;
			FilterCollision(coEvents, coEventsResult,nx,ny);

			//collision logic with other objects
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj))
				{
					if (e->ny < 0)
					{
						//DebugOut(L"vo \n");
						isEnable = false;
						isDie = true;
					}
				}
				else {
					y += dy;
				}
			}
		}

		grid_->Move(this);
		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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