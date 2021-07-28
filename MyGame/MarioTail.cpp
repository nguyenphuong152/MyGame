#include "MarioTail.h"
#include "Mario.h"
#include "MarioStateSpin.h"
#include "Utils.h"
#include "BreakableBrick.h"
#include "Brick.h"
#include "GoomBa.h"
#include "Koopas.h"
#include "RedVenusFireTrap.h"
#include "BoomerangBrother.h"


CMarioTail::CMarioTail()
{
	this->player = CGame::GetInstance()->GetPlayer();
	isEnable = false;
}

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vector<LPCOLLISIONEVENT> coEvents;
	coEvents.clear();

	CalcPotentialCollisions(coObjects, coEvents);

	if (player->marioState != CMarioState::spin.GetInstance())
	{
		if (player->nx > 0)
		{
			SetPosition(player->x, player->y + MARIO_RACOON_BBOX_HEIGHT - 32);
		}
		else {
			SetPosition((player->x + MARIO_RACOON_BBOX_WIDTH -22), player->y + MARIO_RACOON_BBOX_HEIGHT - 32);
		}
	}

	if (CMarioState::spin.GetInstance()->isAttack)
	{
		for (size_t i = 0; i < coObjects->size(); i++)
		{
			if (coObjects->at(i)->isEnable == true && coObjects->at(i)->nx!=0&&AABB(coObjects->at(i)))
			{
				if (dynamic_cast<CBreakableBrick*>(coObjects->at(i)))
				{
					CBreakableBrick* bBrick = dynamic_cast<CBreakableBrick*>(coObjects->at(i));
					if ( bBrick->GetState() == BREAKABLE_BRICK_VISUAL_STATE)
					{
						bBrick->SetAttackedAnimation();
						bBrick->isEnable = false;
					}
				}
				else if (dynamic_cast<CBrick*>(coObjects->at(i)))
			    {
					CBrick* brick = dynamic_cast<CBrick*>(coObjects->at(i));
					if (brick->GetType() == BrickType::twinkle_brick &&  brick->GetState() != BRICK_STATE_TOUCHED)
					{
						brick->SetState(BRICK_STATE_TOUCHED);
					}
					else if (brick->GetType() == BrickType::twinkle_brick_no_item)
					{
						brick->DisableBrick();
					}
				}
				else if (dynamic_cast<CGoomBa*>(coObjects->at(i)))
				{
					CGoomBa* goomba = dynamic_cast<CGoomBa*>(coObjects->at(i));
					if (goomba->GetState() != GOOMBA_STATE_DIE_WITH_DEFLECT)
					{
						goomba->DieWithDeflect(AttackedBy::Tail);
					}
				}
				else if (dynamic_cast<CKoopas*>(coObjects->at(i)))
				{
					CKoopas* koopa = dynamic_cast<CKoopas*>(coObjects->at(i));
					if (koopa->isOnGround && koopa->GetState()!= KOOPA_STATE_DIE)
					{
						koopa->AttackedByTail();
					}
				}
				else if (dynamic_cast<CBoomerangBrother*>(coObjects->at(i)))
				{
					CBoomerangBrother* bmr = dynamic_cast<CBoomerangBrother*>(coObjects->at(i));
					if (bmr->GetState() != BOOMERANGBROTHER_STATE_DIE)
					{
						bmr->SetState(BOOMERANGBROTHER_STATE_DIE);
					}
				}
				else if (dynamic_cast<CRedVenusFireTrap*> (coObjects->at(i)))
				{
					CRedVenusFireTrap* venus = dynamic_cast<CRedVenusFireTrap*>(coObjects->at(i));
					venus->SetAttackedAnimation(AttackedBy::Tail,Points::POINT_300);
					venus->isEnable = false;
				}
			}
		
		}
	}


}

void CMarioTail::Render()
{
	RenderBoundingBox();
}

void CMarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_TAIL_BBOX;
	b = y + MARIO_TAIL_BBOX;
}
