#include "BrownParaGoomBa.h"
#include "Utils.h"
#include "Brick.h"
#include "Ground.h"
#include "PowerUp.h"
#include "MiniGoomba.h"
#include "MiniGoombaPool.h"

CBrownParaGoomba::CBrownParaGoomba()
{
	nx = -1;
	ny = 1;
	SetLevel(GOOMBA_LEVEL_2);
	SetState(BROWN_PARA_GOOMBA_STATE_WALKING);
}

void CBrownParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	if (level == GOOMBA_LEVEL_2)
	{
		l = x;
		t = y;
		r = x + GOOMBA_BBOX_WIDTH;

		if (state == BROWN_PARA_GOOMBA_STATE_WALKING)
		{
			b = y + BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING;
		}
		else {
			b = y + BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY;
		}
	}
	else {
		CGoomBa::GetBoundingBox(l, t, r, b);
	}
}

void CBrownParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (level == GOOMBA_LEVEL_2)
	{
		CEnemy::Update(dt, coObjects);

		CheckGoombaMoving();

		if(state== BROWN_PARA_GOOMBA_STATE_WALKING||state==BROWN_PARA_GOOMBA_STATE_DROP) 
			vy += GOOMBA_GRAVITY * dt;

		//DebugOut(L"%d \n", GetTickCount64() - walking_start);
		if (walking == 1 && GetTickCount64() - walking_start > BROWN_PARA_GOOMBA_WALKING_TIME)
		{
			ChangeStateWhenOverWalkingTime();
		}
		
		//neu bay len qua dat khoang cach chuyen state bay tren troi
		if (y < MAX_DISTANCE_TOP && state == BROWN_PARA_GOOMBA_STATE_FLY)
		{
			SetState(BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR);
		}

		if (state == BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR)
		{
			if (spawning == 1 && GetTickCount64() - spawning_start > SPAWNING_TIME)
			{
				ResetSpawning();
				SpawnMiniGoomba();
			}
		}

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0;

			float rdx = 0, rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			//day object ra mot khoang de k bi chong va cham
			x += min_tx * dx + nx * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			//collision logic with other objects
			for (UINT i = 0; i < coEventsResult.size(); i++)
			{
				LPCOLLISIONEVENT e = coEventsResult[i];

				if (dynamic_cast<CBrick*>(e->obj) || dynamic_cast<CPowerUp*>(e->obj) || dynamic_cast<CGround*>(e->obj))
				{
					if (e->nx != 0)
					{
						this->nx = -this->nx;
						vx = this->nx * GOOMBA_WALKING_SPEED;
					}
					else if (dynamic_cast<CGround*>(e->obj))
					{
						if (e->ny < 0)
						{
							if (state != BROWN_PARA_GOOMBA_STATE_WALKING)
							{
								SetState(BROWN_PARA_GOOMBA_STATE_WALKING);
							}
						}
					}
				}
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
	}
	else {
		CGoomBa::Update(dt, coObjects);
	}
}

void CBrownParaGoomba::Render()
{
	int ani = -1;
	if (level == GOOMBA_LEVEL_2)
	{
		if (state == BROWN_PARA_GOOMBA_STATE_WALKING) ani = BROWN_PARA_GOOMBA_ANI_WALKING;
		else ani = BROWN_PARA_GOOMBA_ANI_FLY;
	}
	else if (level == GOOMBA_LEVEL_1)
	{
		if (state == GOOMBA_STATE_DIE)
		{
			ani = BROWN_PARA_GOOMBA_ANI_DIE;
		}
		else
		{
			ani = BROWN_PARA_GOOMBA_ANI_GOOMBA;
		}
	}

	animation_set->at(ani)->Render(nx, ny, x, y);
	//RenderBoundingBox();
}

void CBrownParaGoomba::CheckGoombaMoving()
{
	if (x < MAX_DISTANCE_LEFT && nx < 0)
	{
		nx = 1;
		SetState(BROWN_PARA_GOOMBA_STATE_WALKING);
	}
	else if (x > MAX_DISTANCE_RIGHT && nx > 0)
	{
		nx = -1;
		SetState(BROWN_PARA_GOOMBA_STATE_WALKING);
	}
}

void CBrownParaGoomba::ChangeStateWhenOverWalkingTime()
{
		ResetWalking();
		if (state == BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR)
		{
			SetState(BROWN_PARA_GOOMBA_STATE_DROP);
		}
		else {
			SetState(BROWN_PARA_GOOMBA_STATE_FLY);
		}
}

void CBrownParaGoomba::SetState(int state)
{
	CGameObject::SetState(state);
	if (level == GOOMBA_LEVEL_2)
	{
		if (state == BROWN_PARA_GOOMBA_STATE_WALKING)
		{
			StartWalking();
			isOnGround = true;
			vx = nx * GOOMBA_WALKING_SPEED;
		}
		else if (state == BROWN_PARA_GOOMBA_STATE_FLY)
		{
			isOnGround = false;
			vy = -HIGH_JUMP_VELOCITY_Y;

		}
		else if (state == BROWN_PARA_GOOMBA_STATE_WALKING_IN_AIR)
		{
			StartWalking();
			SpawnMiniGoomba();
			y = MAX_DISTANCE_TOP;
			vx = nx * GOOMBA_WALKING_SPEED;
			vy = 0;
		}
	}
	else {
		CGoomBa::SetState(state);
	}

}

void CBrownParaGoomba::SpawnMiniGoomba()
{
	CMiniGoomba* minigoomba = CMiniGoombaPool::GetInstance()->Create();
	if (minigoomba != NULL)
	{
		minigoomba->StartSpawning(this);
	}
	StartSpawning();
}
