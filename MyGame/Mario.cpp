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
#include "MarioStateJump.h"
#include "MarioStateFly.h"
#include "MarioStateWalk.h"
#include "MarioStateHoldShellIdle.h"
#include "MarioOverworldState.h"
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
#include "MarioTail.h"
#include "Textures.h"
#include "Card.h"
#include "BoomerangBrother.h"
#include "MagicNoteBlock.h"
#include "WoodBlock.h"
#include "MiniGoomba.h"

//CMario* CMario::__instance = NULL;

CMario::CMario(float x, float y) : CGameObject()
{
	isEnable = true;
	canChangeMap = false;

	level = MARIO_LEVEL_SMALL;
	untouchable = 0;
	InitState();
	nx = 1;

	start_x = x;
	start_y = y;
	SetPosition(x, y);

	SetLive(MARIO_DEFAULT_LIVE);
}

void CMario::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	//calculate dx, 
	CGameObject::Update(dt);
	if (marioState != CMarioState::walking_overworld.GetInstance())
	{
		vy += MARIO_GRAVITY * dt;
	}

	//DebugOut(L"mario vx %f \n", vx);

	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	//turn off collision when die
	if (state != MARIO_STATE_DIE)
		CalcPotentialCollisions(coObjects, coEvents);

	//reset untouchable timer if untouchable time has passed
	if (GetTickCount64() - untouchable_start > MARIO_UNTOUCHABLE_TIME)
	{
		ResetUntouchable();
	}


	if (die == 1 && GetTickCount64() - die_start > MARIO_DIE_TIME)
	{
		Recover();
	}

	CheckMarioOutOfCamera();

	////tru  power khi o trang thai k fly, hoac fly còn dư;
	if (powerMode == false && isOnGround == true) RecalculatePower();

	//if no collision occured, proceed normally
	if (coEvents.size() == 0)
	{
		x += dx;
		y += dy;
	}
	else
	{
		//DebugOut(L"vco event size %d \n", coEvents.size());
		float min_tx, min_ty, nx = 0, ny;

		float rdx = 0, rdy = 0;

		if (state != MARIO_STATE_DIE)
		{
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);
		}

		//// how to push back Mario if collides with a moving objects, what if Mario is pushed this way into another object?
		/*if(rdx != 0 && rdx!=dx)
			x += nx*abs(rdx);*/ 

		//block every object first
		x += min_tx * dx + nx * 0.4f;
		y += min_ty * dy + ny * 0.4f;

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
						goomba->SetAttackedAnimation(AttackedBy::Mario, Points::POINT_100);
						vy = -MARIO_JUMP_DEFLECT_SPEED;
					}
				}
				else if (e->ny > 0)
				{
					y -= MARIO_BIG_BBOX_HEIGHT;
					LevelMarioDown(goomba, BROWN_PARA_GOOMBA_STATE_WALKING);
				}
				else if (e->nx != 0)
				{
					if (untouchable == 0)
						LevelMarioDown(goomba, GOOMBA_STATE_DIE);
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
						koopa->SetState(PARA_KOOPA_STATE_WALKING);
					}
					else if (koopa->GetState() == KOOPA_STATE_DIE)
					{
						koopa->SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
					}
					else {
						koopa->SetState(KOOPA_STATE_DIE);
						koopa->StartDie();
					}
					koopa->SetAttackedAnimation(AttackedBy::Mario, Points::POINT_100);
					vy = -MARIO_JUMP_DEFLECT_SPEED;

				}
				else if (e->nx != 0)
				{
					if (koopa->GetState() == KOOPA_STATE_DIE)
					{
						if (powerMode)
						{
							ChangeState(CMarioState::holdshell_idle.GetInstance());
							isHoldKoopa = true;
							//koopa->isHolded = true;
						}
						else {
							ChangeState(CMarioState::kick.GetInstance());
							CMarioState::kick.GetInstance()->StartKicking();
							koopa->SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
						}
					}
					else if (untouchable == 0)
					{
						LevelMarioDown(koopa, KOOPA_STATE_DIE);
					}
				}
			}
			else if (dynamic_cast<CPortal*>(e->obj))
			{
				CPortal* p = dynamic_cast<CPortal*>(e->obj);
				SetPosition(p->x + 2, p->y - 2);
				CMarioState::walking_overworld.GetInstance()->SetSceneSwitching(p->GetSceneId());
			}
			else if (dynamic_cast<CGround*>(e->obj) || dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
					//set state idle khi vao scene bi mat
					if (dynamic_cast<CGround*>(e->obj))
					{
						canGoIntoPipe = false;
						if (CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe == true)
						{
							CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe = false;
							ChangeState(CMarioState::idle.GetInstance());
						}
					}
				}
				else if (e->ny > 0)
				{
					if (dynamic_cast<CBox*>(e->obj))
					{
						if (marioState == CMarioState::go_to_pipe.GetInstance() ||
							marioState == CMarioState::fly.GetInstance() || marioState == CMarioState::jump.GetInstance())
						{
							y += dy;
						}
					}
				}
				else if (e->nx != 0)
				{
					if (dynamic_cast<CBox*>(e->obj))
					{
						x += dx;
					}
					else if (dynamic_cast<CGround*>(e->obj))
					{
						RecalculatePower();
						ChangeState(CMarioState::walk.GetInstance());
					}
				}
			}
			else if (dynamic_cast<CBoundary*>(e->obj))
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
					else {
						y += dy;
					}
				}
				else if (e->ny < 0)
				{
					Die();
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
						if (brick->GetType() == BrickType::twinkle_brick_coin)
						{
							brick->isTouch = true;
						}
						else if (brick->GetType() == BrickType::twinkle_brick_no_item)
						{
							if (level > MARIO_LEVEL_SMALL)
							{
								brick->SetAttackedAnimation();
							}
						}
					}
				}

			}
			else if (dynamic_cast<CObjectBoundary*>(e->obj)) //when reach boundary for koopa
			{
				if (e->nx != 0)x += dx;
				if (e->ny != 0)y += dy;
			}
			else if (dynamic_cast<CSwitch*>(e->obj)) //when reach boundary for koopa
			{
				if (e->ny != 0)
				{
					y += dy;
					if (e->ny < 0)
					{
						if (dynamic_cast<CSwitch*>(e->obj))
						{
							CSwitch* switch_item = dynamic_cast<CSwitch*>(e->obj);
							isOnGround = true;
							switch_item->SetState(SWITCH_STATE_TOUCHED);
							isJumpOnSwitch = true;
						}
					}
				}
			}
			else if (dynamic_cast<CCoin*>(e->obj) || dynamic_cast<CPowerUp*>(e->obj) || dynamic_cast<COneUpMushroom*>(e->obj))
			{
				(e->obj)->isEnable = false;
				if (dynamic_cast<CPowerUp*>(e->obj))
				{
					if (level < MARIO_LEVEL_RACOON)
					{
						ChangeState(CMarioState::transform.GetInstance());
						CMarioState::transform.GetInstance()->StartTransform();
						LevelUp();
					}
				}
				else if (dynamic_cast<COneUpMushroom*>(e->obj))
				{
					live++;
				}
				y -= 1;
			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj))
			{
				CBreakableBrick* breakable_brick = dynamic_cast<CBreakableBrick*>(e->obj);

				if (breakable_brick->GetState() == BREAKABLE_BRICK_VISUAL_STATE)
				{
					if (e->ny < 0)
					{
						isOnGround = true;
						isFloating = false;
					}
				}
				else if (breakable_brick->GetState() == BREAKABLE_BRICK_COIN_STATE)
				{
					breakable_brick->isEnable = false;
				}
			}
			else if (dynamic_cast<CPipe*>(e->obj)) {
				CPipe* pipe = dynamic_cast<CPipe*>(e->obj);
				if (marioState == CMarioState::go_to_pipe.GetInstance() && CMarioState::go_to_pipe.GetInstance()->isChangeState == 0)
				{
					y += dy;
				}
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
					else if (pipe->GetType() == PipeType::hidden)
					{
						CMarioState::go_to_pipe.GetInstance()->isTouchHiddenPipe = true;
						this->nx = 1;
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
						SetPosition(x + 10, y);
					}
					else if (pipe->GetType() == PipeType::exit)
					{
						CMarioState::go_to_pipe.GetInstance()->SetPostionOut(pipe->x, pipe->y);
					}
				}
			}
			else if (dynamic_cast<CCard*>(e->obj))
			{
				CCard* card = dynamic_cast<CCard*>(e->obj);
				if (e->ny > 0)
				{
					card->SetState(CARD_STATE_TOUCH);
				}
			}
			else if (dynamic_cast<CBoomerangBrother*>(e->obj))
			{
				CBoomerangBrother* bBrother = dynamic_cast<CBoomerangBrother*>(e->obj);
				if (e->ny < 0)
				{
					bBrother->SetState(BOOMERANGBROTHER_STATE_DIE);
					bBrother->StartDie();
				}
			}
			else if (dynamic_cast<CMagicNoteBlock*>(e->obj))
			{
				CMagicNoteBlock* magicBlock = dynamic_cast<CMagicNoteBlock*>(e->obj);
				if (e->ny < 0)
				{
					isFloating = false;
					vx = 0;

					if ((magicBlock->GetState() != MAGIC_NOTE_BLOCK_STATE_JUMPING&&magicBlock->GetType()==MagicNoteBlockType::visible)||
						(magicBlock->GetType() == MagicNoteBlockType::invisible && magicBlock->invisible == false))
					{
						magicBlock->SetState(MAGIC_NOTE_BLOCK_STATE_JUMPING, JUMP_ON);
					}

					if ((magicBlock->GetType() == MagicNoteBlockType::invisible && magicBlock->invisible == true))
					{
						isOnGround = true;
					}
				}
				else if (e->ny > 0)
				{
					magicBlock->SetState(MAGIC_NOTE_BLOCK_STATE_JUMPING, JUMP_UNDER);
					if (magicBlock->GetType() == MagicNoteBlockType::invisible)
					{
						magicBlock->VisualBlock();
					}
				}
			}
			else if (dynamic_cast<CWoodBlock*>(e->obj))
			{
				CWoodBlock* woodBlock = dynamic_cast<CWoodBlock*>(e->obj);
				if (e->nx != 0)
				{
					vx = e->nx * FORCE_PUSH_MARIO_AWAY;
					woodBlock->SetState(WOOD_BLOCK_STATE_TOUCHED, e->nx);
				}
				else if (e->ny < 0)
				{
					isOnGround = true;
					isFloating = false;
				}
			}
			else if (dynamic_cast<CMiniGoomba*>(e->obj))
			{
				CMiniGoomba* g = dynamic_cast<CMiniGoomba*>(e->obj);
				isStuckWithMiniGoomba = true;
				if (e->nx != 0)
				{
					//DebugOut(L"hello \n");
					if (g->GetState() != MINIGOOMBA_STATE_SURROUND_MARIO)
					{
						g->SetState(MINIGOOMBA_STATE_SURROUND_MARIO);
					}
				}
				else if (e->ny != 0)
				{
					y -= 1;
					if (g->GetState() != MINIGOOMBA_STATE_SURROUND_MARIO)
					{
						g->SetState(MINIGOOMBA_STATE_SURROUND_MARIO);
					}
				}
			}
			else if (dynamic_cast<CRedVenusFireTrap*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					CRedVenusFireTrap* venus = dynamic_cast<CRedVenusFireTrap*>(e->obj);
					LevelMarioDown(venus, VENUS_STATE_GO_UP);
				}
			}
			else if (dynamic_cast<CFireball*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					CFireball* ball = dynamic_cast<CFireball*>(e->obj);
					LevelMarioDown(ball, FIREBALL_STATE_FIRE);
					if (e->ny < 0)
					{
						y -= 3;
					}
				}
            }
		}
	}

	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];

	//neu k phai ow moi cho update tail
	if (CGame::GetInstance()->current_scene != OVERWORLD_MAP)
	{
		tail->Update(dt, coObjects);
	}
	marioState->Update(dt, *this);

//DebugOut(L"%f  %f\n", x, y);
}

void CMario::Render()
{
	int ani = GetCurrentAnimation();
	if (state == MARIO_STATE_DIE) ani = MARIO_ANI_DIE;
	int alpha = 255;

	if (untouchable) alpha = 128;
	animation_set->at(ani)->Render(nx, 1, x, y, alpha);
	RenderBoundingBox();


	/*if (level == MARIO_LEVEL_RACOON)
	{
		RenderRaccoonMarioBoundingBox();
	}
	else {
		RenderBoundingBox();
	}*/
}

void  CMario::SetState(int state)
{
	CGameObject::SetState(state);
	if (state == MARIO_STATE_DIE) {
		vy = -MARIO_DIE_DEFLECT_SPEED;
		vx = 0;
		StartDie();
	}
}

void CMario::InitState() {
	if (CGame::GetInstance()->current_scene != OVERWORLD_MAP)
	{
		marioState = CMarioState::idle.GetInstance();
	}
	else {
		marioState = CMarioState::walking_overworld.GetInstance();
	}
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
	if (object->GetState() != enemy_condition||dynamic_cast<CBrownParaGoomba*>(object)
		||dynamic_cast<CRedVenusFireTrap*>(object)||dynamic_cast<CFireball*>(object)
		)
	{
		StartUntouchable();
		if (level <MARIO_LEVEL_SMALL)
		{
			Die();
		}
		else {
			level--;
		}
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

		if (nx == -1)
		{
			r = x + MARIO_RACOON_BBOX_WIDTH - 10;
		}
	}
	else if (marioState == CMarioState::walking_overworld.GetInstance())
	{
		r = x + MARIO_SMALL_BBOX_WIDTH;
		b = y + MARIO_SMALL_BBOX_HEIGHT-8;
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
	nx = 1;
	tail->isEnable = true;
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

void CMario::SwitchOverworld()
{
	CGame::GetInstance()->SwitchScene(4);
}

void CMario::Recover()
{
	ResetDie();
	SetState(MARIO_STATE_ALIVE);

	isStuckWithMiniGoomba = false;

	InitState();
	SetPosition(start_x, start_y);
	CGame::GetInstance()->GetMainCamera()->InitCamera();
}

void CMario::LevelUp()
{
	if (level < MARIO_LEVEL_RACOON) level++;

	y -= MARIO_RACOON_BBOX_HEIGHT - MARIO_SMALL_BBOX_HEIGHT;
}

void  CMario::AttachTail(CMarioTail* nTail)
{
	tail = nTail;
}

void CMario::CheckMarioOutOfCamera()
{
	float cx, cy;
	CGame::GetInstance()->GetMainCamera()->GetPosition(cx, cy);
	if (y < cy)
	{
		marioState = CMarioState::drop.GetInstance();
		y += dy;
	}
}

void CMario::RenderRaccoonMarioBoundingBox()
{
	RECT rect = CalculateRect();

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	if (nx == 1)
	{
		CGame::GetInstance()->Draw(0, 0, x + 20, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
	}
	else {
		CGame::GetInstance()->Draw(0, 0, x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
	}
}

//CMario* CMario::GetInstance()
//{
//	if (__instance == NULL) __instance = new CMario();
//	return __instance;
//}
