#include "MiniGoomba.h"
#include "Game.h"
#include "Utils.h"
#include "ObjectBoundary.h"
#include "Box.h"
#include "Ground.h"

CMiniGoomba::CMiniGoomba()
{
	_state.live.inUse = false;
	_state.live.isSurroundMario = false;
	_state.live.direction = -1;
}

void CMiniGoomba::StartSpawning(CBrownParaGoomba* goomba)
{
	//DebugOut(L"do mini goomba %f\n",goomba->x);
	CMario* player = CGame::GetInstance()->GetPlayer();
	SetPosition(goomba->x - 3, goomba->y + 5);
	if (goomba->x > player->x) nx = -1;
	else nx = 1;

	isEnable = true;
	_state.live.inUse = true;
	_state.live.isSurroundMario = false;
	_state.live.direction = nx;

	vx = nx * MINIGOOMBA_VELOCITY_X;

	StartChangeDirection();
	StartLiving();
}

void CMiniGoomba::Render()
{
	//DebugOut(L"hello \n");
	animation_set->at(0)->Render(1, 1, x, y);
	//RenderBoundingBox();
}

void CMiniGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* colObject) {
	
	colObject->push_back(this);
	
	CGameObject::Update(dt, colObject);
	x += dx;
	y += dy;

	if (state == MINIGOOMBA_STATE_SURROUND_MARIO) {
		CMario* player = CGame::GetInstance()->GetPlayer();

		if (player->state != MARIO_STATE_DIE)
		{
			if (x > player->x + MARIO_BIG_BBOX_WIDTH)
			{
				vx = -MINIGOOMBA_VELOCITY_X / 2;
			}
			else if (x < player->x-5)
			{
				vx = MINIGOOMBA_VELOCITY_X / 2;
			}

			if (y > player->y + MARIO_BIG_BBOX_HEIGHT - MINIGOOMBA_BBOX_WIDTH)
			{
			   vy = -MINIGOOMBA_SPINNING_VELOCITY_Y;
			}
			vy += MINIGOOMBA_GRAVITY/2;
		}
		else {
			SetState(MINIGOOMBA_STATE_NORMAL);
		}
	}
	else {
		vy += MINIGOOMBA_GRAVITY;

		vx = MINIGOOMBA_VELOCITY_X * _state.live.direction;

		if (GetTickCount64() - _state.live.changeDirection_start > MINIGOOMBA_FLOATING_TIME && _state.live.changeDirection == 1)
		{
			ResetChangeDirection();
			_state.live.direction = -_state.live.direction;
			StartChangeDirection();
		}

		if (GetTickCount64() - _state.live.alive_start > MINIGOOMBA_LIVING_TIME && _state.live.alive == 1)
		{
			SetState(MINIGOOMBA_STATE_NORMAL);
			ResetLive();
		}
	}
}

//void CMiniGoomba::DisableBoomerangByCamera()
//{
//
//	CCamera* cam = CGame::GetInstance()->GetMainCamera();
//	if (AABB(cam) == false) {
//		DisableBoomerang();
//	}
//}


void CMiniGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = l + MINIGOOMBA_BBOX_WIDTH;
	b = t + MINIGOOMBA_BBOX_WIDTH;
}

void CMiniGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MINIGOOMBA_STATE_SURROUND_MARIO)
	{
		_state.live.isSurroundMario = true;
	}
	else {
		_state.live.isSurroundMario = false;
		_state.live.inUse = false;
		vy = 0;
	}
}

bool CMiniGoomba::FinishShooting()
{
	if (_state.live.inUse == false && isEnable ) return true;
	else return false;
}


