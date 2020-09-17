#include "GoomBa.h"

CGoomBa::CGoomBa()
{
	SetState(GOOMBA_STATE_WALKING);
}

void CGoomBa::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GOOMBA_BBOX_WIDTH;

	if (state == GOOMBA_STATE_DIE)
		b = y + GOOMBA_BBOX_HEIGHT_DIE;
	else
		b = y + GOOMBA_BBOX_HEIGHT;
}

void CGoomBa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);


	//
	// TO-DO: make sure Goomba can interact with the world and to each of them too!
	// 

	x += dx;
	y += dy;

	if (vx < 0 && x < 0)
	{
		x = 0;
		vx = -vx;
	}

	if (vx > 0 && x > 290)
	{
		x = 290;
		vx = -vx;
	}
}

void CGoomBa::Render()
{
	int ani = GOOMBA_ANI_WALKING;
	if (state == GOOMBA_STATE_DIE)
	{
		ani = GOOMBA_ANI_DIE;
	}

	//change direction for goomba
	animation_set->at(ani)->Render(1,x, y);
}

void CGoomBa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case GOOMBA_STATE_DIE:
		y += GOOMBA_BBOX_HEIGHT - GOOMBA_BBOX_HEIGHT_DIE + 1;
		vx = 0;
		vy = 0;
		break;
	case GOOMBA_STATE_WALKING:
		vx = -GOOMBA_WALKING_SPEED;
		break;
	}
}