#include "MagicNoteBlock.h"
#include "Game.h"
#include "Utils.h"
#include "MarioStateDrop.h"
#include "MarioStateJump.h"

CMagicNoteBlock::CMagicNoteBlock(float x, float y, MagicNoteBlockType type)
{
	this->type = type;
	isEnable = true;
	if (type == MagicNoteBlockType::invisible) invisible = true;

	player = CGame::GetInstance()->GetPlayer();

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
		CMario* p = CGame::GetInstance()->GetPlayer();
		if (y > start_y&& dir ==JUMP_ON)
		{
			
			p->isOnMagicBlock = true;
			vy += -MAGIC_NOTE_RETURN_SPEED;
		}
		else if (y < start_y&& dir==JUMP_UNDER)
		{
			vy += MAGIC_NOTE_RETURN_SPEED;
		}
		else {
			if (dir == JUMP_ON)
			{
				p->isOnMagicBlock = false;
				p->vy = -PLAYER_DEFLECT;
			}
			y = start_y;
			vy = 0;
			SetState(MAGIC_NOTE_BLOCK_STATE_NORMAL, NORMAL);
		}
	}
	
}


void CMagicNoteBlock::Render()
{
	int ani = -1;
	if (type==MagicNoteBlockType::visible)
	{
		animation_set->at(MAGIC_NOTE_ANI_NORMAL)->Render(-1, 1, x, y);
	}
	else if(type==MagicNoteBlockType::invisible && invisible == false){
		animation_set->at(MAGIC_NOTE_ANI_INVISIBLE)->Render(-1, 1, x, y);
	}
	//RenderBoundingBox();
}

void CMagicNoteBlock::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MAGIC_NOTE_BLOCK_BBOX_WIDTH;
	b = y + MAGIC_NOTE_BLOCK_BBOX_WIDTH;
}

