#include "Koopas.h"
#include "Utils.h"
#include "MarioStateIdle.h"
#include "MarioStateKick.h"
#include "Boundary.h"
#include "Box.h"
#include "ObjectBoundary.h"
#include "Ground.h"
#include "Brick.h"
#include "Pipe.h"
#include "Camera.h"
#include "PowerUp.h"
#include "EffectPool.h"
#include "MarioStateHoldShellIdle.h"
#include "BreakableBrick.h"
#include "MagicNoteBlock.h"
#include "Grid.h"
#include "Coin.h"
#include "BoomerangBrother.h"
#include "Boomerang.h"


CKoopas::CKoopas()
{
	nx = -1;
	ny = 1;
	isOnGround = false;
	recover = 0;
	_recoverStart = 0;
	SetLevel(KOOPA_LEVEL_1);
	SetState(KOOPA_STATE_WALKING);
}

void CKoopas::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	r = x + KOOPA_BBOX_WIDTH;

	if (state == KOOPA_STATE_DIE || state == KOOPA_STATE_DIE_WITH_VELOCITY || state == KOOPA_STATE_RECOVER)
	{
		t = y;
		b = y + KOOPA_BBOX_HEIGHT_DIE;
	}
	else
	{
		t = y;
		b = y + KOOPA_BBOX_HEIGHT;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	CGameObject::Update(dt);

	if (player->isHoldKoopa == true && state == KOOPA_STATE_DIE)
	{
		UpdateShellPosition();
	}
	else {
		vy += KOOPA_GRAVITY * dt;
	}

	////die ->recover
	if (state == KOOPA_STATE_DIE)
	{
		if ((GetTickCount64() - CEnemy::die_start) > KOOPA_DIE_TIME && die) {
			ResetDie();
			y -= KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
			SetState(KOOPA_STATE_RECOVER);
		}
	}
	////recover->live
	if (GetTickCount64() - _recoverStart > KOOPA_RECOVER_TIME && recover) {
		ResetRecover();
		y -= KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
		if (this->ny == -1) this->ny = 1;
		SetLevel(KOOPA_LEVEL_1);
		SetState(KOOPA_STATE_WALKING);
	}

	if (player->GetState() == CMarioState::kick.GetInstance() 
		&& player->isHoldKoopa && state == KOOPA_STATE_DIE)
	{
		SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
	}

	//DebugOut(L"state %d\n", state);

	HandleCollision(coObjects);
	grid_->Move(this);
}



void CKoopas::Render()
{
	int ani = KOOPA_ANI_WALKING;
	if (state == KOOPA_STATE_DIE)
		ani = KOOPA_ANI_DIE;
	else if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
		ani = KOOPA_ANI_DIE_WITH_VELOCITY;
	else if (state == KOOPA_STATE_RECOVER)
		ani = KOOPA_ANI_RECOVER;

	//change direction for koopas
	animation_set->at(ani)->Render(nx, ny, x, y);
	//RenderBoundingBox();
}

void CKoopas::HandleCollision(vector<LPGAMEOBJECT>* coObjects)
{
	//collision logic with other objects
	vector<LPCOLLISIONEVENT> coEvents;
	vector<LPCOLLISIONEVENT> coEventsResult;

	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (coEvents.size() == 0)
	{
		y += dy;
		x += dx;
	}
	else
	{
		float nx = 0, ny;
		FilterCollision(coEvents, coEventsResult, nx, ny);
		for (UINT i = 0; i < coEventsResult.size(); i++)
		{
			LPCOLLISIONEVENT e = coEventsResult[i];

			if (dynamic_cast<CBrick*>(e->obj))
			{
				if (e->nx != 0)
				{
					CBrick* brick = dynamic_cast<CBrick*>(e->obj);
					ChangeDirection();
					if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						if (brick->GetState() == BRICK_STATE_UNTOUCH && brick->GetType() == BrickType::question_brick)
						{
							brick->SetState(BRICK_STATE_TOUCHED);
						}
						else if (brick->GetType() == BrickType::twinkle_brick_no_item) {
							brick->DisableBrick();
						}
					}
				}
				else if (e->ny != 0)
				{
					isOnGround = true;
				}
			}
			else if (dynamic_cast<CBreakableBrick*>(e->obj))
			{
				CBreakableBrick* bBrick = dynamic_cast<CBreakableBrick*>(e->obj);
				if (e->nx != 0)
				{
					if (bBrick->GetState() == BREAKABLE_BRICK_COIN_STATE)
					{
						WalkThrough();
					}
					else if (bBrick->GetState() == BREAKABLE_BRICK_VISUAL_STATE)
					{
						ChangeDirection();
						if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
						{
							bBrick->SetAttackedAnimation();
						}
					}
				}
				if (e->ny < 0)
				{
					if (bBrick->GetState() == BREAKABLE_BRICK_COIN_STATE)
					{
						isOnGround = false;
						y += dy;
					}
				}
			}
			else if (dynamic_cast<CObjectBoundary*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (GetState() == KOOPA_STATE_WALKING)
						ChangeDirection();
					else if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY )
						WalkThrough();
				}
			}
			else if (dynamic_cast<CGround*>(e->obj))
			{
				if (e->nx != 0)
					ChangeDirection();
				else if (e->ny < 0)
					isOnGround = true;
			}
			else if (dynamic_cast<CMagicNoteBlock*>(e->obj))
			{
				if (e->nx != 0)
				{
					CMagicNoteBlock* block = dynamic_cast<CMagicNoteBlock*>(e->obj);
					if (block->invisible == true)
						WalkThrough();
					else 
						ChangeDirection();
				}
				else if (e->ny < 0)
					isOnGround = true;

			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny < 0)
					isOnGround = true;
				else if(e->nx!=0)
					WalkThrough();
			}
			else if (dynamic_cast<CCoin*>(e->obj)||dynamic_cast<CBoomerang*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
					WalkThrough();
			}
			else if (dynamic_cast<CGoomBa*>(e->obj))
			{
				CGoomBa* goomba = dynamic_cast<CGoomBa*>(e->obj);
				if ( e->nx!=0)
				{
					if (goomba->GetState() != GOOMBA_STATE_DIE_WITH_DEFLECT && state == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						goomba->DieWithDeflect(AttackedBy::KoopaShell);
					}
					WalkThrough();
				}
			}
			else if (dynamic_cast<CBoomerangBrother*>(e->obj))
			{
			    CBoomerangBrother* bmr = dynamic_cast<CBoomerangBrother*>(e->obj);
				if (e->nx != 0)
				{
					WalkThrough();
					if (bmr->GetState() !=BOOMERANGBROTHER_STATE_DIE && state == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						bmr->SetState(BOOMERANGBROTHER_STATE_DIE);
					}
				}
			}
			else if (dynamic_cast<CKoopas*>(e->obj))
			{
				CKoopas* koopa = dynamic_cast<CKoopas*>(e->obj);
				if ( e->nx!=0)
				{
					if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						isEnable = false;
						if (koopa->GetState() == KOOPA_STATE_WALKING)
							koopa->AttackedByTail();
						else if (koopa->GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
							koopa->isEnable = false;
					}
					else {
						WalkThrough();
					}
					
				}
			}
			else if (dynamic_cast<CEnemy*>(e->obj))
			{
				x += dx;
				y += dy;
			}
			else if (dynamic_cast<CBoundary*>(e->obj))
			{
				isEnable = false;
			}
		}
	}
	for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
}

void CKoopas::LevelDown()
{
	level--;
	if (level == 0) {
		SetState(KOOPA_STATE_DIE);
		StartDie();
	}
	else if (level == KOOPA_LEVEL_1)
	{
		SetState(KOOPA_STATE_WALKING);
	}
	SetAttackedAnimation(AttackedBy::Mario, Points::POINT_100);
}

void CKoopas::SetStateWhenPlayerJumpOn()
{
	if (state == KOOPA_STATE_DIE)
		SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
	else LevelDown();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		vx = 0;
		StartDie();
		break;
	case KOOPA_STATE_WALKING:
		vx = this->nx * KOOPA_WALKING_SPEED;
		player->isHoldKoopa = false;
		break;
	case KOOPA_STATE_DIE_WITH_VELOCITY:
		player->isHoldKoopa = false;
		this->nx = player->nx;
		vx = KOOPA_SHELL_VELOCITY_X * this->nx;
		break;
	case KOOPA_STATE_RECOVER:
		vx = 0;
		CEnemy::die_start = 0;
		die = 0;
		StartRecover();
		SetLevel(KOOPA_LEVEL_1);
		break;
	}
}

void CKoopas::UpdateShellPosition()
{
	if (player->nx > 0)
	{
		x = player->x + VALUE_ADJUST_SHELL + 20;
		if (player->GetLevel() != MARIO_LEVEL_RACOON)
		{
			x = player->x + VALUE_ADJUST_SHELL + 2;
		}
	}
	else {
		x = player->x - VALUE_ADJUST_SHELL;
	}

	y = player->y - 2;
	if (player->GetLevel() != MARIO_LEVEL_SMALL) y = player->y + VALUE_ADJUST_SHELL + 2;
}

void CKoopas::AttackedByTail()
{
	if (level == KOOPA_LEVEL_2) SetLevel(KOOPA_LEVEL_1);
	ny = -1;
	vx = 0.1f;
	vy = -KOOPA_DEFLECT_SPEED;
	SetState(KOOPA_STATE_DIE);

	SetAttackedAnimation(AttackedBy::Tail, Points::POINT_300);
}

void CKoopas::ChangeDirection()
{
	float speed = -1.0f;
	if (state == KOOPA_STATE_WALKING)
		speed = KOOPA_WALKING_SPEED;
	else if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
		speed = KOOPA_SHELL_VELOCITY_X;

	this->nx = -this->nx;
	vx = speed * this->nx;
}

void CKoopas::WalkThrough()
{
	float speed = -1.0f;
	if (state == KOOPA_STATE_WALKING)
		speed = KOOPA_WALKING_SPEED;
	else if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
		speed = KOOPA_SHELL_VELOCITY_X;

	vx = speed * this->nx;
	x += dx;
}
