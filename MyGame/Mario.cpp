#include <algorithm>
#include <assert.h>
#include "Utils.h"
#include "Game.h"
#include "MarioState.h"
#include "MarioStateIdle.h"
#include "MarioStateRun.h"
#include "MarioStateDrop.h"
#include "MarioStateGetIntoPipe.h"
#include "MarioStateTransform.h"
#include "MarioStateSpin.h"
#include "MarioStateFly.h"
#include "MarioStateHoldShellIdle.h"
#include "Goomba.h"
#include "Portal.h"
#include "Ground.h"
#include "Box.h"
#include "Brick.h"
#include "Pipe.h"
#include "Koopas.h"
#include "MarioStateKick.h"
#include "Boundary.h"
#include "Camera.h"
#include "FireBallPool.h"
#include "ObjectBoundary.h"
#include "ParaGoomba.h"
#include "ParaKoopa.h"
#include "Coin.h"
#include "Piranha.h"
#include "BreakableBrick.h"
#include "Switch.h"
#include "PowerUp.h"
#include "RedVenusFireTrap.h"
#include "One-upMushroom.h"

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
	SetLive(MARIO_DEFAULT_LIVE);
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
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		untouchable_start = 0;
		untouchable = 0;
	}
	////tru  power khi o trang thai k fly, hoac fly còn dư;
	if(powerMode == false && isOnGround == true) RecalculatePower();

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
		for (UINT i = 0; i < coEventsResult.size(); i++)
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

						if (goomba->GetLevel() == GOOMBA_LEVEL_2)
						{
							goomba->SetLevel(GOOMBA_LEVEL_1);
							goomba->SetState(GOOMBA_STATE_WALKING);
						}
						else
						{
							goomba->SetState(GOOMBA_STATE_DIE);
							goomba->StartDie();
						}
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->nx != 0)
				{
					if (CMarioState::spin.GetInstance()->isAttack)
					{
						if (goomba->GetLevel() == GOOMBA_LEVEL_2)
						{
							goomba->SetLevel(GOOMBA_LEVEL_1);
						}
						goomba->SetState(GOOMBA_STATE_DIE_WITH_DEFLECT);
						goomba->vy = -GOOMBA_DEFLECT_SPEED;
						goomba->ny = -1;
					}
					/*	else
						{
							if (untouchable == 0)
								LevelMarioDown(goomba, GOOMBA_STATE_DIE);
						}*/
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj)) //if e->obj is Goomba
			{
				CKoopas* koopa = dynamic_cast<CKoopas*>(e->obj);
				//jummp  on top >> kill koopas and deflect a bit
				if (e->ny < 0)
				{
					if (koopa->GetLevel() == KOOPA_LEVEL_2)
					{
						koopa->SetLevel(KOOPA_LEVEL_1);
						if (CMarioState::spin.GetInstance()->isAttack)
						{
							koopa->AttackedByTail();
						}
						else {
							koopa->SetState(PARA_KOOPA_STATE_WALKING);
						}
					}
					else {
						koopa->SetState(KOOPA_STATE_DIE);
						koopa->StartDie();
					}
					vy = -MARIO_JUMP_DEFLECT_SPEED;
				}
				else if (e->nx != 0)
				{
					if (CMarioState::spin.GetInstance()->isAttack)
					{
						if (koopa->GetState() == KOOPA_STATE_WALKING)
						{
							koopa->AttackedByTail();
						}

					}
					else if (koopa->GetState() == KOOPA_STATE_DIE)
					{
						isKicking = true;
						ChangeState(CMarioState::kick.GetInstance());
						CMarioState::kick.GetInstance()->StartKicking();
						if (canHoldShell)
						{
							ChangeState(CMarioState::holdshell_idle.GetInstance());
							koopa->isHolded = true;
							isKicking = false;
						}
					}
					/*	else if (untouchable == 0)
						{
							LevelMarioDown(koopa, KOOPA_STATE_DIE);
						}*/
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				CGame::GetInstance()->SwitchScene(p->GetSceneId());
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				CGround* ground = dynamic_cast<CGround*>(e->obj);
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
					canGoIntoPipe = false;
					if (CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe == true)
					{
						CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe = false;
						ChangeState(CMarioState::idle.GetInstance());
					}
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
					if (marioState == CMarioState::run.GetInstance())
						vx = MARIO_RUNNING_SPEED * this->nx;
				}
			}
			else if (dynamic_cast<CBoundary*>(e->obj) || dynamic_cast<CCamera*>(e->obj))
			{
				if (e->ny > 0)
				{
					if (marioState == CMarioState::fly.GetInstance())
					{
						ChangeState(CMarioState::drop.GetInstance());
						powerMode = false;
					}
					else if (marioState == CMarioState::go_to_pipe.GetInstance())
					{
						if (!CMarioState::go_to_pipe.GetInstance()->isUp)vy = -MARIO_IN_PIPE_VELOCITY_Y;
						else vy = MARIO_IN_PIPE_VELOCITY_Y;
					}
					y += dy;
				}
				else if (e->ny < 0)
				{
					CCamera::GetInstance()->InactiveCamera();
				}
			}
			else if (dynamic_cast<CBrick*>(e->obj))
			{
				CBrick* brick = dynamic_cast<CBrick*>(e->obj);
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
				}

				if (brick->GetState() == BRICK_STATE_UNTOUCH)
				{
					if (e->ny > 0) {
						brick->SetState(BRICK_STATE_TOUCHED);
						canJumpHigh = false;
					}
				}
				if (brick->GetType() == BrickType::twinkle_brick && brick->GetState() != BRICK_STATE_TOUCHED)
				{

					if (e->nx != 0 && CMarioState::spin.GetInstance()->isAttack)
					{
						brick->SetState(BRICK_STATE_TOUCHED);
					}
				}

			}
			else if (dynamic_cast<CObjectBoundary*>(e->obj)) //when reach boundary for koopa
			{
				if (e->nx != 0) x += dx;
				else if (e->ny != 0) y += dy;
			}
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				CCoin* coin = dynamic_cast<CCoin*>(e->obj);
				if (e->nx != 0 || e->ny != 0)
				{
					coin->isEnable = false;
				}
			}
			else if (dynamic_cast<CPiranha*> (e->obj))
			{
				CPiranha* piranha = dynamic_cast<CPiranha*>(e->obj);
				if (e->nx != 0 && CMarioState::spin.GetInstance()->isAttack)
				{
					piranha->SetAttackedAnimation();
					piranha->isEnable = false;
				}
			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj))
			{
				CBreakableBrick* breakable_brick = dynamic_cast<CBreakableBrick*>(e->obj);
				if (breakable_brick->GetState() == BREAKABLE_BRICK_COIN_STATE)
				{
					breakable_brick->isEnable = false;
				}
				else
				{
					if (CMarioState::spin.GetInstance()->isAttack && e->nx != 0)
					{
						breakable_brick->SetAttackedAnimation();
						breakable_brick->isEnable = false;
					}
					else if (e->ny < 0)
					{
						isOnGround = true;
						isFloating = false;
					}
				}
			}
			else if (dynamic_cast<CSwitch*>(e->obj))
			{
				x += dx;
				y += dy;
				CSwitch* switch_item = dynamic_cast<CSwitch*>(e->obj);
				if (e->ny < 0)
				{
					isOnGround = true;
					switch_item->SetState(SWITCH_STATE_TOUCHED);
					isJumpOnSwitch = true;
				}
			}
			else if (dynamic_cast<CPowerUp*>(e->obj))
			{
				CPowerUp* power = dynamic_cast<CPowerUp*> (e->obj);
				if (power->isActive)
				{
					if (level < MARIO_LEVEL_RACOON)
					{
						ChangeState(CMarioState::transform.GetInstance());
						CMarioState::transform.GetInstance()->StartTransform();
						LevelUp();
					}
					power->isEnable = false;
				}
			}
			else if (dynamic_cast<CRedVenusFireTrap*>(e->obj))
			{
				CRedVenusFireTrap* venus = dynamic_cast<CRedVenusFireTrap*>(e->obj);
				if (e->nx != 0 && CMarioState::spin.GetInstance()->isAttack)
				{
					venus->SetAttackedAnimation();
					venus->isEnable = false;
				}
			}
			else if (dynamic_cast<COneUpMushroom*>(e->obj))
			{
				COneUpMushroom* mushroom = dynamic_cast<COneUpMushroom*>(e->obj);
				live++;
				mushroom->isEnable = false;
			}
			else if (dynamic_cast<CPipe*>(e->obj)) {
				CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
					canGoIntoPipe = false;
					//neu dung vo pipe co loi vao thi bat cờ , đợi ng chơi nhấn down thì di xuống
					if (pipe->GetType() == PipeType::entry)
					{
						canGoIntoPipe = true;
						CMarioState::go_to_pipe.GetInstance()->SetPositionChangeCam(pipe->x, pipe->y + 6);
					}
				}
				else if (e->ny > 0)
				{
					if (pipe->GetType() == PipeType::hidden)
					{
						
						ChangeState(CMarioState::go_to_pipe.GetInstance());
						CMarioState::go_to_pipe.GetInstance()->SetPositionChangeCam(pipe->x, pipe->y - 30);
						CMarioState::go_to_pipe.GetInstance()->isUp = true;
						CMarioState::go_to_pipe.GetInstance()->inPipe = 1;
						SetPosition(x + 20, y);
					}
				}
				if (marioState == CMarioState::go_to_pipe.GetInstance()&& CMarioState::go_to_pipe.GetInstance()->isChangeState==0)
				{
					y += dy;
					if (e->ny > 0)
					{
						if (pipe->GetType() == PipeType::exit)
						{
							CMarioState::go_to_pipe.GetInstance()->SetPostionOut(pipe->x, pipe->y);
						}
					}
					else if (e->ny < 0)
					{
						if (pipe->GetType() == PipeType::hidden)
						{
							CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe = true;
							this->nx = 1;
						}
					}
				}
			}
		}
	}
	marioState->Update(dt, *this);

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CMario::Render()
{
	int ani = GetCurrentAnimation();
	if (state == MARIO_STATE_DIE) ani = MARIO_ANI_DIE;
	int alpha = 255;

	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(nx, 1, x, y, alpha);
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

void CMario::RecalculatePower()
{
	if (powerLevel <= MARIO_POWER_LEVEL && powerLevel >= 10) {
	   powerLevel -= 10;
	}
}

void CMario::HandleInput(Input input)
{
	marioState->HandleInput(*this, input);
	marioState->Enter(*this);
}

void CMario::LevelMarioDown(CGameObject* object, int enemy_condition)
{
	if (object->GetState() != enemy_condition)
	{
		if (level > MARIO_LEVEL_SMALL)
		{
			level = MARIO_LEVEL_SMALL;
			StartUntouchable();
		}
		SetState(MARIO_STATE_DIE);
	}
}

void CMario::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	if (level == MARIO_LEVEL_BIG || level == MARIO_LEVEL_FIRE)
	{
		r = x + MARIO_BIG_BBOX_WIDTH;
		b = y + MARIO_BIG_BBOX_HEIGHT;
	}
	else if (level == MARIO_LEVEL_RACOON || level == MARIO_LEVEL_IMMORTAL) {
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
	else if (marioState == CMarioState::go_to_pipe.GetInstance())
	{
		l = x - 60;
		r = x + MARIO_BIG_BBOX_WIDTH - 12;
	}
}

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

void CMario::ImmortalMario()
{
	InitState();
	SetLevel(MARIO_LEVEL_IMMORTAL);
	y -= 100;
	SetSpeed(0, 0);
	nx = 1;
}

void CMario::Die()
{
	SetState(MARIO_STATE_DIE);
}

void CMario::LevelUp()
{
	if (level < MARIO_LEVEL_RACOON) level++;

	y -= MARIO_RACOON_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
}

CMario* CMario::GetInstance()
{
	if (__instance == NULL) __instance = new CMario();
	return __instance;
}
