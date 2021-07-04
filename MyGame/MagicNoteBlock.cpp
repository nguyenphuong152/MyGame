#include "MagicNoteBlock.h"
#include "Game.h"
#include "Utils.h"

CMagicNoteBlock::CMagicNoteBlock(float x, float y)
{
	player = CGame::GetInstance()->GetPlayer();
	isEnable = true;
	SetAnimation(MAGIC_NOTE_BLOCK_ANI);
	SetState(MAGIC_NOTE_BLOCK_STATE_NORMAL,NORMAL);
	SetPosition(x, y);
	start_y = y;
}

void CMagicNoteBlock::SetState(int state, int direction)
{
	CGameObject::SetState(state);
	if (state == MAGIC_NOTE_BLOCK_STATE_JUMPING)
	{
		dir = direction;
		if (direction ==JUMP_ON) vy = MAGIC_NOTE_DEFLECT_SPEED;
		else if(direction==JUMP_UNDER)vy = -MAGIC_NOTE_DEFLECT_SPEED;
	}
	else {
		vy = 0;
	}
}

void CMagicNoteBlock::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	y += dy;

	if (state == MAGIC_NOTE_BLOCK_STATE_JUMPING) {
		if (y > start_y&& dir ==JUMP_ON)
		{
			//DebugOut(L"%f ----- %f \n", y, start_y);
			vy -= MAGIC_NOTE_RETURN_SPEED;
		}
		else if (y < start_y&& dir==JUMP_UNDER)
		{
			vy += MAGIC_NOTE_RETURN_SPEED;
		}
		else {
			y = start_y;
			SetState(MAGIC_NOTE_BLOCK_STATE_NORMAL, NORMAL);
		}
	}
	
}


void CMagicNoteBlock::Render()
{
	int ani = -1;
	/*if (state == MAGIC_NOTE_BLOCK_STATE_NORMAL)
		ani = MAGIC_NOTE_ANI_NORMAL;
	else
		ani = MAGIC_NOTE_ANI_JUMPING;*/
	animation_set->at(0)->Render(-1, 1, x, y);
	//RenderBoundingBox();
}

void CMagicNoteBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MAGIC_NOTE_BLOCK_BBOX_WIDTH;
	b = y + MAGIC_NOTE_BLOCK_BBOX_WIDTH;
}

