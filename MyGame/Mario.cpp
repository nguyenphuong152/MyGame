#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Game.h"
#include "MarioState.h"
#include "MarioStateIdle.h"
#include "MarioStateDrop.h"
#include "MarioStateHoldShellIdle.h"
#include "Goomba.h"
#include "Portal.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"
#include "Pipe.h"
#include "Items.h"
#include "Koopas.h"
#include "MarioStateKick.h"
#include "Boundary.h"
#include "Camera.h"
#include "FireBallPool.h"

CMario* CMario::__instance = NULL;

CMario::CMario(float x, float y) : CGameObject()
{
	isEnable = true;
	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	InitState();
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

	vy += MARIO_GRAVITY * dt;
	
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

	//tru  power khi o trang thai k fly, hoac fly còn dư;
	if (!powerMode && powerLevel <= MARIO_POWER_LEVEL && powerLevel >= 10) powerLevel -= 10;

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

		if (state != MARIO_STATE_DIE)
		{
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}


		// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		//if (rdx != 0 && rdx!=dx)
		//	x += nx*abs(rdx); 

		//block every object first
		x += min_tx * dx + nx * 0.25f;
		y += min_ty * dy + ny * 0.25f;

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
						goomba->isEnable = false;
						goomba->StartDie();
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
							SetState(MARIO_STATE_DIE);
						}
					}
				}

			}
			else if (dynamic_cast<CKoopas*>(e->obj)) //if e->obj is Goomba
			{
				CKoopas* koopas = dynamic_cast<CKoopas*>(e->obj);
				//jummp  on top >> kill koopas and deflect a bit
				if (e->ny < 0)
				{
					if (koopas->GetState() != KOOPAS_STATE_DIE)
					{
						koopas->SetState(KOOPAS_STATE_DIE);
						//koopas->isEnable = false;
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx!=0)
				{
					if (koopas->GetState() == KOOPAS_STATE_DIE)
					{
						if (canHoldShell)
						{
							ChangeState(CMarioState::holdshell_idle.GetInstance());
							koopas->isHolded = true;
						}
					}
				}
				/*else if (e->nx != 0)
				{
					if (untouchable == 0)
					{
						if (koopas->GetState() != KOOPAS_STATE_DIE)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								level = MARIO_LEVEL_SMALL;
								StartUntouchable();
							}
							SetState(MARIO_STATE_DIE);
						}
					}
				}*/

			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CGround*>(e->obj) || dynamic_cast<CPipe*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
				}
			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
				}
				else if (e->nx != 0)
				{
					x += dx;
				}
			}
			else if (dynamic_cast<CBoundary*>(e->obj)||dynamic_cast<CCamera*>(e->obj))
			{
				if (e->ny != 0)
				{
					ChangeState(CMarioState::drop.GetInstance());
					powerMode = false;
					y += dy;
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny != 0)
				{
					isOnGround = true;
					isFloating = false;
					//cục gạch chưa touch mới vào xét
					if (brick->GetState() == BRICK_STATE_UNTOUCH)
					{
						if (e->ny > 0)
						{
							brick->SetState(BRICK_STATE_TOUCHED);
						}
					}
				}
			}
		}
	}

	marioState->Update(dt, *this);

	for (UINT i = 0;i < coEvents.size();i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = GetCurrentAnimation();
	if (state == MARIO_STATE_DIE) ani = MARIO_ANI_DIE;
	int alpha = 255;

	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(nx,x, y, alpha);
	//RenderBoundingBox();
}

void  CMario::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MARIO_STATE_DIE) {
		vy = -MARIO_DIE_DEFLECT_SPEED;
	}
}

void CMario::InitState() {
	marioState = CMarioState::idle.GetInstance();
}

void CMario::HandleInput(Input input)
{
	marioState->HandleInput(*this, input);
	marioState->Enter(*this);
}



void CMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (level == MARIO_LEVEL_BIG||level==MARIO_LEVEL_FIRE)
	{
		r = x + MARIO_BIG_BBOX_WIDTH;
		b = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if(level == MARIO_LEVEL_RACOON) {
		r = x + MARIO_RACOON_BBOX_WIDTH;
		b = y + MARIO_RACOON_BBOX_HEIGHT;
	}
	else {
		r = x + MARIO_SMALL_BBOX_WIDTH;
		b = y + MARIO_SMALL_BBOX_HEIGHT;
	}
	if (isSitting)
	{
		b = y + MARIO_BIG_BBOX_SIT_HEIGHT;
	}
}

//void CMario::ThrowFireball()
//{
//	CFireBallPool::GetInstance()->Create();
//	if (fireball != NULL) fireball->AllocateFireballToMario();
//}

/*
	reset mario status to the beginning state of a scene
*/

void CMario::BigMario()
{
	InitState();
	SetLevel(MARIO_LEVEL_BIG);
	SetSpeed(0, 0);
	y -= 100;
	nx = 1;
}

void CMario::RaccoonMario()
{
	InitState();
	SetLevel(MARIO_LEVEL_RACOON);
	y -= 100;
	SetSpeed(0, 0);
	nx = 1;
}

void CMario::FireMario()
{
	InitState();
	SetLevel(MARIO_LEVEL_FIRE);
	y -= 100;
	SetSpeed(0, 0);
	nx = 1;
}

void CMario::Die()
{
	SetState(MARIO_STATE_DIE);
}

//void CMario::CheckCollisionWithItems(vector<LPGAMEOBJECT>* listItem)
//{
//	float mario_left, mario_top, mario_right, mario_bottom,
//		item_left, item_top, item_right, item_bottom;
//
//	GetBoundingBox(mario_left, mario_top, mario_right, mario_bottom);
//	
//
//	for (UINT i = 0;i < listItem->size();i++)
//	{	
//		if (listItem->at(i)->isStop) continue;
//		listItem->at(i)->GetBoundingBox(item_left, item_top, item_right, item_bottom);
//
//		if (CGameObject::AABB(mario_left, mario_top, mario_right, mario_bottom,
//			item_left, item_top, item_right, item_bottom))
//		{
//			listItem->at(i)->isEnable = false;
//			listItem->at(i)->isStop = true;
//			int state = listItem->at(i)->GetState();
//			switch (state)
//			{
//			case ITEM_MUSHROOM:
//				
//				SetLevel(MARIO_LEVEL_BIG);
//				//xét lại vị trí của mario khi mario ở size bự, nếu k xét bị lọt xuống k có ground để đỡ mario
//				y -= MARIO_BIG_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
//				break;
//			}
//		}
//	}
//}
//


CMario* CMario::GetInstance()
{
	if (__instance == NULL) __instance = new CMario();
	return __instance;
}
