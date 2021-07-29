#include "Chest.h"
#include "MagicWhistle.h"
#include "Mario.h"
#include "Game.h"

CChest::CChest(CGameObject* item)
{
	isEnable = true;
	this->item = item;
	SetObjectAnimation(CHEST_ANI);
}

void CChest::Render()
{
	int ani = -1;
	if (state == CHEST_STATE_UNTOUCH)
		ani = CHEST_ANI_UNTOUCH;
	else ani = CHEST_ANI_TOUCHED;
	animation_set->at(ani)->Render(-1, 1, x, y);
}

void CChest::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + CHEST_BBOX_WIDTH;
	b = t + CHEST_BBOX_WIDTH;
}

void CChest::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == CHEST_STATE_TOUCHED)
	{
		if (dynamic_cast<CMagicWhistle*>(item))
		{
			CMagicWhistle* magic_whistle = dynamic_cast<CMagicWhistle*>(item);
			magic_whistle->SetState(MAGIC_WHISTLE_STATE_ACTIVE);
		}
	}
}

void CChest::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject)
{
	CMario* player = CGame::GetInstance()->GetPlayer();
	if (AABB(player) && player->GetInput() == Input::PRESS_A)
		SetState(CHEST_STATE_TOUCHED);
}
