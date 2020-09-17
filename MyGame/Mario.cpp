#include <algorithm>
#include <assert.h>
#include "Utils.h"

#include "Mario.h"
#include "Game.h"

#include "Goomba.h"
#include "Portal.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"


CMario::CMario(float x, float y) : CGameObject()
{
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	SetState(MARIO_STATE_IDLE);
	nx = 1;
	start_x = x;
	start_y = y;
	this->x = x;
	this->y = y;
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//calculate dx, dy
	CGameObject::Update(dt);

	//check whether mario go outside map
	if (x < 10)
		x = 15;
	
	vy += MARIO_GRAVITY * dt;

	//DebugOut(L"[INFO]vy: %f \n",vy);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//turn off collision when die
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	//reset untouchable timer if untouchable time has passed
	if (GetTickCount() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}

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

		// TODO: This is a very ugly designed function!!!!
		FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);


		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		//block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

		if (nx != 0) vx = 0;
		if (ny != 0) vy = 0;

		//collision logic with other objects
		for (UINT i = 0;i < coEventsResult.size();i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];
			if (dynamic_cast<CGoomBa*>(e->obj)) //if e->obj is Goomba
			{
				CGoomBa* goomba = dynamic_cast<CGoomBa*>(e->obj);
				//jummp  on top >> kill goomba and deflect a bit
				if (e->ny < 0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE)
					{
						goomba->SetState(GOOMBA_STATE_DIE);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (goomba->GetState() != GOOMBA_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							else
							{
								SetState(MARIO_STATE_DIE);
							}
						}
					}
				}

			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->ny < 0)
				{
					isJumping = false;
				}
			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny != 0)
				{
					isJumping = false;
				}
				else
				{
					x += dx;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->ny != 0)
				{
					isJumping = false;
				}
			}
		}
	}

	//DebugOut(L"[INFO]vy: %f \n", vy);

	for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = -1;
	if (state == MARIO_STATE_DIE)
		ani = MARIO_ANI_DIE;
	/*else if (level == MARIO_LEVEL_BIG)
	{
		if (vx == 0)
		{
			if (nx > 0) ani = MARIO_ANI_BIG_IDLE_RIGHT;
			else  ani = MARIO_ANI_BIG_IDLE_LEFT;
		}
		else if (vx > 0)
		{
			ani = MARIO_ANI_BIG_WALKING_RIGHT;
		}
		else ani = MARIO_ANI_BIG_WALKING_LEFT;
	}*/
	else if (level == MARIO_LEVEL_SMALL)
	{
		/*switch (state)
		{
			case MARIO_STATE_WALKING:
				ani = MARIO_ANI_SMALL_WALKING;
				break;
			case MARIO_STATE_JUMP:
				if (vy>0)
				{
					ani = MARIO_ANI_JUMP;
				}
				break;
			case MARIO_STATE_IDLE:
				ani = 
				break;
		}*/
		if (vx == 0)
		{
			ani = MARIO_ANI_SMALL_IDLE;
			if (vy != 0 && isJumping)
			{
				ani = MARIO_ANI_JUMP;
			}
		}
		else if (vx != 0)
		{
			ani = MARIO_ANI_SMALL_WALKING;
		}
}


	int alpha = 255;

	if (untouchable)

		alpha = 128;


	animation_set->at(ani)->Render(nx,x, y, alpha);

	RenderBoundingBox();
}

void  CMario::SetState(int state)
{
	CGameObject::SetState(state);

	switch (state)
	{
	case MARIO_STATE_WALKING:
		if (nx > 0)
		{
			vx = MARIO_WALKING_SPEED;
		}
		else
		{
			vx = -MARIO_WALKING_SPEED;
		}
		break;
	case MARIO_STATE_JUMP:
		vy = -MARIO_JUMP_SPEED_Y;
	case MARIO_STATE_IDLE:
		vx = 0;
		break;
	case MARIO_STATE_DIE:
		vy = -MARIO_DIE_DEFLECT_SPEED;
		break;
	}
}

void CMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;

	/*if (level == MARIO_LEVEL_BIG)
	{
		r = x + MARIO_BIG_BBOX_WIDTH;
		b = y + MARIO_BIG_BBOX_HEIGHT;
	}*/
	
		r = x + MARIO_SMALL_BBOX_WIDTH;
		b = y + MARIO_SMALL_BBOX_HEIGHT;
	
}

/*
	reset mario status to the beginning state of a scene
*/

void CMario::Reset()
{
	SetState(MARIO_STATE_IDLE);
	SetLevel(MARIO_LEVEL_SMALL);
	SetPosition(start_x, start_y);
	SetSpeed(0, 0);
	SetDirection(1);
}

void CMario::Jumping()
{
	SetState(MARIO_STATE_JUMP);
	isJumping = true;
}

