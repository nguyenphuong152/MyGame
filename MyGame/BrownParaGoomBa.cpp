#include "BrownParaGoomBa.h"
#include "Utils.h"
#include "Brick.h"
#include "Ground.h"
#include "PowerUp.h"
#include "MiniGoomba.h"
#include "MiniGoombaPool.h"
#include "Grid.h"

CBrownParaGoomba::CBrownParaGoomba()
{
	spawning = walking = 0;
	spawning_start = walking_start =0;
	nx = -1;
	ny = 1;
	SetLevel(GOOMBA_LEVEL_2);
	SetState(GOOMBA_STATE_WALKING);
}

void CBrownParaGoomba::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + GOOMBA_BBOX_WIDTH;

	if (level == GOOMBA_LEVEL_2)
	{
		if (state == GOOMBA_STATE_WALKING)
		{
			b = y + BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_WALKING;
		}
		else {
			b = y + BROWN_PARA_GOOMBA_LEVEL_2_BBOX_HEIGHT_FLY;
		}
	}
	else if (state == GOOMBA_STATE_WALKING) b = y + GOOMBA_BBOX_HEIGHT;
	else b = y + GOOMBA_BBOX_HEIGHT_DIE;
}

void CBrownParaGoomba::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (level == GOOMBA_LEVEL_2)
	{
		vx = nx * GOOMBA_WALKING_SPEED;
		CheckGoombaMoving();

		if (walking == 1 && GetTickCount64() - walking_start > BROWN_PARA_GOOMBA_WALKING_TIME)
		{
			ChangeStateWhenOverWalkingTime();
		}

	    //dang bay giu lai de de minigoomba
		if (vy > 0 && state == BROWN_PARA_GOOMBA_STATE_FLY) {
			vy = -BROWN_PARA_GOOMBA_SHORT_JUMP_VELOCITY_Y;
			if (spawning == 1 && GetTickCount64() - spawning_start > SPAWNING_TIME)
			{
				ResetSpawning();
				SpawnMiniGoomba();
			}
		}
		if (isOnGround && walking == 0) SetState(GOOMBA_STATE_WALKING);

	}
	CGoomBa::Update(dt, coObjects);
}

void CBrownParaGoomba::Render()
{
	int ani = -1;

	if (level == GOOMBA_LEVEL_2)
	{
		if (state == GOOMBA_STATE_WALKING) ani = BROWN_PARA_GOOMBA_ANI_WALKING;
		else ani = BROWN_PARA_GOOMBA_ANI_FLY;
	}
	else if (state == GOOMBA_STATE_WALKING || state == GOOMBA_STATE_DIE_WITH_DEFLECT) 
		ani = BROWN_PARA_GOOMBA_ANI_GOOMBA;
	else ani = BROWN_PARA_GOOMBA_ANI_DIE;

	//DebugOut(L"x y goomba %d -- %d \n", state, ani);
	animation_set->at(ani)->Render(nx, ny, x, y);
	//RenderBoundingBox();
}


void CBrownParaGoomba::CheckGoombaMoving()
{
	if (x < MAX_DISTANCE_LEFT && nx < 0) nx = 1;
	else if (x > MAX_DISTANCE_RIGHT && nx > 0) nx = -1;
}

void CBrownParaGoomba::ChangeStateWhenOverWalkingTime()
{
	ResetWalking();
	if (state == BROWN_PARA_GOOMBA_STATE_FLY)
	{
		SetState(BROWN_PARA_GOOMBA_STATE_DROP);
	}
	else {
		SetState(BROWN_PARA_GOOMBA_STATE_FLY);
	}
}

void CBrownParaGoomba::SetState(int state)
{
	CGoomBa::SetState(state);
	if (state == GOOMBA_STATE_WALKING)
	{
		StartWalking();
	}
	else if (state == BROWN_PARA_GOOMBA_STATE_FLY)
	{
		isOnGround = false;
		vy = -BROWN_PARA_GOOMBA_HIGH_JUMP_VELOCITY_Y;
		StartWalking();
		SpawnMiniGoomba();
	}
}

void CBrownParaGoomba::SpawnMiniGoomba()
{
	//DebugOut(L"hello \n");
	CMiniGoomba* minigoomba = CMiniGoombaPool::GetInstance()->Create();
	if (minigoomba != NULL)
	{
		//DebugOut(L"k null \n");
		minigoomba->StartSpawning(this);
		
	}
	StartSpawning();
	
}
