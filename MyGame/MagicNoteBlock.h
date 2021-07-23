
#pragma once
#include "GameObject.h"
#include "Mario.h"

#define MAGIC_NOTE_BLOCK_STATE_NORMAL   100
#define MAGIC_NOTE_BLOCK_STATE_JUMPING	200

#define MAGIC_NOTE_ANI_NORMAL 0
#define MAGIC_NOTE_ANI_INVISIBLE	1

#define  MAGIC_NOTE_BLOCK_BBOX_WIDTH	48

#define MAGIC_NOTE_BLOCK_ANI	45

#define MAGIC_NOTE_DEFLECT_SPEED 0.5f
#define MAGIC_NOTE_RETURN_SPEED	0.08f

#define PLAYER_DEFLECT 0.5f

#define JUMP_ON -1
#define JUMP_UNDER 1
#define NORMAL	0

enum class MagicNoteBlockType {
	visible,
	invisible
};

class CMagicNoteBlock : public CGameObject
{
	MagicNoteBlockType type;

	float start_y;
	int dir;
	CMario* player;
public:
	bool invisible = false;
	CMagicNoteBlock(float x, float y, MagicNoteBlockType type);

	MagicNoteBlockType GetType() { return type; };
	void VisualBlock() { invisible = false; };

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state, int direction);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};
