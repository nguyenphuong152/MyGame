#include "Koopas.h"
#include "Utils.h"
#include "Mario.h"

CKoopas::CKoopas(float start_point,float end_point,CMario *player)
{
	isEnable = true;
	this->player = player;
	this->start_point = start_point;
	this->end_point = end_point;
	nx = 1;
	SetState(KOOPAS_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + KOOPAS_BBOX_WIDTH;

	if (state == KOOPAS_STATE_DIE)
	{
		t = y;
		b = y + KOOPAS_BBOX_HEIGHT_DIE;
	}
	else
	{
		t = y + 20;
		b = y + KOOPAS_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt, coObjects);

	x += dx;
	y += dy;

	if(isHolded)
	{
		if (player->nx > 0)
		{
			x = player->x + 17.5;
			if (player->level != MARIO_LEVEL_RACOON)
			{
				x = player->x + 11;
			}
		}
		else {
			x = player->x - 13;
			if (player->level == MARIO_LEVEL_RACOON)
			{
				x = player->x - 12;
			}
		}

		if (player->level == MARIO_LEVEL_SMALL)
		{
			y = player->y;
		}
		else {
			y = player->y + 7;
		}
		
	}

	if (player->isKicking)
	{
		vx = player->nx * 0.33;
		isHolded = false;
		player->isKicking = false;
	}

	if (vx < 0 && x < start_point)
	{
		x = start_point; vx = -vx;
	}

	if (vx > 0 && x > end_point)
	{
		x = end_point; vx = -vx;
	}
}

void CKoopas::Render()
{
	int ani = KOOPAS_ANI_WALKING;
	if (state == KOOPAS_STATE_DIE)
	{
		ani = KOOPAS_ANI_DIE;
	}
	else if (vx > 0) nx = 1;
	else if (vx <= 0) nx = -1;

	//change direction for koopas
	animation_set->at(ani)->Render(nx,x, y);

	RenderBoundingBox();
}


void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPAS_STATE_DIE:
		y += KOOPAS_BBOX_HEIGHT - KOOPAS_BBOX_HEIGHT_DIE + 6;
		vx = 0;
		vy = 0;
		break;
	case KOOPAS_STATE_WALKING:
		vx = nx*KOOPAS_WALKING_SPEED;
		break;
	}
}
