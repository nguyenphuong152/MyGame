
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MAGIC_NOTE_BLOCK_STATE_NORMAL   100
#define MAGIC_NOTE_BLOCK_STATE_JUMPING	200

#define MAGIC_NOTE_ANI_NORMAL 0
#define MAGIC_NOTE_ANI_JUMPING	1

#define  MAGIC_NOTE_BLOCK_BBOX_WIDTH	45

#define MAGIC_NOTE_BLOCK_ANI	45

#define MAGIC_NOTE_DEFLECT_SPEED 0.2
#define MAGIC_NOTE_RETURN_SPEED	0.02

#define JUMP_ON -1
#define JUMP_UNDER 1
#define NORMAL	0

class CMagicNoteBlock : public CGameObject
{
	float start_y;
	int dir;
	CMario* player;
public:
	CMagicNoteBlock(float x, float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state, int direction);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
