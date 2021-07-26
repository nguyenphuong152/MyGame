#include "WoodBlock.h"
#include "PowerUp.h"
#include "Utils.h"

CWoodBlock::CWoodBlock(CGameObject* item, float x)
{
	this->item = item;
	SetObjectAnimation(WOOD_BLOCK_ANI);
	isEnable = true;
	SetState(WOOD_BLOCK_STATE_UNTOUCH,0);
	oldX = x;
}


void CWoodBlock::Render()
{
	int ani = -1;
	if (state == WOOD_BLOCK_STATE_UNTOUCH)
	{
		ani = WOOD_BLOCK_ANI_UNTOUCH;
	}
	else 
	{
		ani = WOOD_BLOCK_ANI_TOUCHED;
	}
	//RenderBoundingBox();
	animation_set->at(ani)->Render(-1, 1, x, y);
}

void CWoodBlock::SetState(int state, float dir)
{
	this->dir = dir;
	CGameObject::SetState(state);
	if (state == WOOD_BLOCK_STATE_TOUCHED)
	{
		if (this->dir < 0)
			vx = WOOD_BLOCK_SPEED;
		else vx = -WOOD_BLOCK_SPEED;

		if (dynamic_cast<CPowerUp*>(item))
		{
			CPowerUp* powerup = dynamic_cast<CPowerUp*>(item);
			powerup->DefinePowerUpType();
			powerup->SetState(POWERUP_STATE_GO_UP);
		}
	}
}

void CWoodBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	if (state == WOOD_BLOCK_STATE_TOUCHED)
	{
		if (dir < 0)
		{
			vx -= WOOD_BLOCK_TURNBACK_SPEED;
		}
		else {
			vx += WOOD_BLOCK_TURNBACK_SPEED;
		}
		x += dx;
	}
	if (x <= oldX && dir <0||x>=oldX&&dir>0)
	{
		x = oldX;
		vx = 0;
		SetState(WOOD_BLOCK_STATE_UNTOUCH, 0);
	}
}

void CWoodBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + WOOD_BLOCK_BBOX_WIDTH;
	b = y + WOOD_BLOCK_BBOX_WIDTH;
}
