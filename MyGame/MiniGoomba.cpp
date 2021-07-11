#include "MiniGoomba.h"
#include "Game.h"
#include "Utils.h"
#include "ObjectBoundary.h"
#include "Box.h"
#include "Ground.h"

CMiniGoomba::CMiniGoomba()
{
	_state.live.inUse = false;
}

void CMiniGoomba::StartSpawning(CBrownParaGoomba* goomba)
{
	CMario* player = CGame::GetInstance()->GetPlayer();
	SetPosition(goomba->x, goomba->y + 5);
	if (goomba->x > player->x) nx = -1;
	else nx = 1;

	isEnable = true;
	_state.live.inUse = true;
	_state.live.goomba = goomba;
	_state.live.direction = nx;

	vx = nx * MINIGOOMBA_VELOCITY_X;
	StartChangeDirection();
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
    
	if (state == MINIGOOMBA_STATE_SURROUND_MARIO) {
		DebugOut(L"asdfd \n");
	}
	else {
		vy += MINIGOOMBA_GRAVITY;

		vx = MINIGOOMBA_VELOCITY_X * _state.live.direction;

		if (GetTickCount64() - _state.live.changeDirection_start > FLOATING_TIME && _state.live.changeDirection == 1)
		{
			ResetChangeDirection();
			_state.live.direction = -_state.live.direction;
			StartChangeDirection();
		}
	}

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(colObject, coEvents);

	//if no collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;

		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

		////block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny != 0)
				{
					isEnable = false;
				}
			}
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
 		vx = 0;
	}
}

bool CMiniGoomba::FinishShooting()
{
	if (!_state.live.inUse) return false;
	else if (!isEnable)
	{
		_state.live.inUse = false;
		return true;
	}
	else return false;
}


