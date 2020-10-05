#include "Brick.h"
#include "Utils.h"
#include "Mario.h"
#include "Items.h"

CBrick::CBrick(int itemId)
{
	isEnable = true;
	this->itemId = itemId;
	SetState(BRICK_STATE_UNTOUCH);
}

void CBrick::Render()
{
		int ani;
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
		//nếu touch cục gạch, dùng biến oldY lưu vị trí cũ để khi nó nhảy lên biết vị trí cũ để về
		oldY = y;
		// vị trí mới khi bị touch
		y -= BRICK_DEFLECT_POS;
	}
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
		if (state == BRICK_STATE_TOUCHED && isDropItem) {
			//DebugOut(L"drop \n");
			return;
		}
		CGameObject::Update(dt, coObjects);
		if (state == BRICK_STATE_TOUCHED && !isDropItem)
		{
			if (y < oldY)
			{
				y++;//để nó nhảy lên xong về lại vị trí cũ
			}	
			else {
				isDropItem = true;
				//DebugOut(L"vo \n");
			}
		}
}

void CBrick::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + BRICK_BBOX_WIDTH;
	b = y + BRICK_BBOX_HEIGHT;
}


