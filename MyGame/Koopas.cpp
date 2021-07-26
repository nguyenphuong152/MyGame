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


CKoopas::CKoopas()
{
	nx = 1;
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

	//////die ->recover
	//if (state != KOOPA_STATE_DIE_WITH_VELOCITY)
	//{
	//	if ((GetTickCount64() - CEnemy::die_start) > KOOPA_DIE_TIME && die) {
	//		y -= KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
	//		SetState(KOOPA_STATE_RECOVER);
	//	}
	//}
	//////recover->live
	//if (GetTickCount64() - _recoverStart > KOOPA_RECOVER_TIME && recover) {
	//	//xet lai vi tri k thoi rua se bi roi xuong
	//	y -= KOOPA_BBOX_HEIGHT - KOOPA_BBOX_HEIGHT_DIE;
	//	if (ny == -1) ny = 1;
	//	SetState(KOOPA_STATE_WALKING);
	//}

	if (player->GetState() == CMarioState::kick.GetInstance() 
		&& player->isHoldKoopa && state == KOOPA_STATE_DIE)
	{
		DebugOut(L"alooo \n");
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
					if (GetState() == KOOPA_STATE_WALKING)
					{
						ChangeDirection(KOOPA_WALKING_SPEED);
					}
					else if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						if (brick->GetState() == BRICK_STATE_UNTOUCH && brick->GetType() == BrickType::question_brick)
						{
							brick->SetState(BRICK_STATE_TOUCHED);
						}
						else if (brick->GetType() == BrickType::twinkle_brick_no_item) {
							brick->DisableBrick();
						}
						ChangeDirection(KOOPA_SHELL_VELOCITY_X);
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
					if (GetState() == KOOPA_STATE_WALKING && bBrick->GetState() == BREAKABLE_BRICK_COIN_STATE)
					{
						WalkThrough(KOOPA_WALKING_SPEED);
					}
					else if (bBrick->GetState() == BREAKABLE_BRICK_VISUAL_STATE)
					{
						if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
						{
							ChangeDirection(KOOPA_SHELL_VELOCITY_X);
							bBrick->SetAttackedAnimation();
						}
						else {
							ChangeDirection(KOOPA_WALKING_SPEED);
						}
					}
				}
				if (e->ny < 0)
				{
					if (bBrick->GetState() == BREAKABLE_BRICK_COIN_STATE && GetState() == KOOPA_STATE_WALKING)
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
					{
						ChangeDirection(KOOPA_WALKING_SPEED);
					}
					else if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY)
					{
						WalkThrough(KOOPA_SHELL_VELOCITY_X);
					}
				}
			}
			else if (dynamic_cast<CGround*>(e->obj) || dynamic_cast<CMagicNoteBlock*>(e->obj))
			{
				if (e->nx != 0)
				{
					if (GetState() == KOOPA_STATE_WALKING)
					{
						ChangeDirection(KOOPA_WALKING_SPEED);
					}
					else {
						ChangeDirection(KOOPA_SHELL_VELOCITY_X);
					}
				}
				else if (e->ny < 0)
				{
					isOnGround = true;
				}
			}
			else if (dynamic_cast<CBox*>(e->obj))
			{
				if (e->ny < 0)
				{
					isOnGround = true;
				}
			}
			else if (dynamic_cast<CCoin*>(e->obj))
			{
				if (e->nx != 0 || e->ny != 0)
				{
					if (state == KOOPA_STATE_WALKING)
						WalkThrough(KOOPA_WALKING_SPEED);
					else WalkThrough(KOOPA_SHELL_VELOCITY_X);
				}
			}
			if (GetState() == KOOPA_STATE_DIE_WITH_VELOCITY && e->nx != 0)
			{
				WalkThrough(KOOPA_SHELL_VELOCITY_X);
				if (dynamic_cast<CGoomBa*>(e->obj))
				{
					CGoomBa* goomba = dynamic_cast<CGoomBa*>(e->obj);
					if (goomba->GetState() != GOOMBA_STATE_DIE_WITH_DEFLECT)
					{
						goomba->DieWithDeflect(AttackedBy::KoopaShell);
					}
				}
				else if (dynamic_cast<CKoopas*>(e->obj))
				{
					CKoopas* koopa = dynamic_cast<CKoopas*>(e->obj);
					if (koopa->isOnGround)
					{
						koopa->AttackedByTail();
					}
				}
			}else if (dynamic_cast<CEnemy*>(e->obj))
			{
				x += dx;
				y += dy;
			}

			if (dynamic_cast<CBoundary*>(e->obj))
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
	SetState(KOOPA_STATE_WALKING);
	if (level == 0) {
		SetState(KOOPA_STATE_DIE);
		StartDie();
	}
	else {
		SetAttackedAnimation(AttackedBy::Mario, Points::POINT_100);
	}
}

void CKoopas::SetStateWhenPlayerJumpOn()
{
	if (state == KOOPA_STATE_DIE)
		SetState(KOOPA_STATE_DIE_WITH_VELOCITY);
	else if (state == KOOPA_STATE_DIE_WITH_VELOCITY)
		SetState(KOOPA_STATE_DIE);
	else LevelDown();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case KOOPA_STATE_DIE:
		vx = 0;
		break;
	case KOOPA_STATE_WALKING:
		vx = nx * KOOPA_WALKING_SPEED;
		break;
	case KOOPA_STATE_DIE_WITH_VELOCITY:
		player->isHoldKoopa = false;
		vx = KOOPA_SHELL_VELOCITY_X * player->nx;
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
	vy = -KOOPA_DEFLECT_SPEED;
	SetState(KOOPA_STATE_DIE);

	SetAttackedAnimation(AttackedBy::Tail, Points::NONE);
}

void CKoopas::ChangeDirection(float speed)
{
	this->nx = -this->nx;
	vx = speed * this->nx;
}

void CKoopas::WalkThrough(float speed)
{
	vx = speed * this->nx;
	x += dx;
}
