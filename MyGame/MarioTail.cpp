#include "MarioTail.h"
#include "Mario.h"
#include "MarioStateSpin.h"
#include "Utils.h"
#include "BreakableBrick.h"
#include "Brick.h"
#include "GoomBa.h"
#include "Koopas.h"
#include "RedVenusFireTrap.h"


CMarioTail::CMarioTail(vector<LPGAMEOBJECT>& obj)
{
	this->player = CGame::GetInstance()->GetPlayer();
	this->objects = obj;
	isEnable = false;
}

void CMarioTail::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{

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
		for (size_t i = 0; i < objects.size(); i++)
		{
			if (objects[i]->isEnable == true && objects[i]->nx!=0&&AABB(objects[i]))
			{
				if (dynamic_cast<CBreakableBrick*>(objects[i]))
				{
					CBreakableBrick* bBrick = dynamic_cast<CBreakableBrick*>(objects[i]);
					if ( bBrick->GetState() == BREAKABLE_BRICK_VISUAL_STATE)
					{
						bBrick->SetAttackedAnimation();
						bBrick->isEnable = false;
					}
				}
				else if (dynamic_cast<CBrick*>(objects[i]))
			    {
					CBrick* brick = dynamic_cast<CBrick*>(objects[i]);
					if (brick->GetType() == BrickType::twinkle_brick &&  brick->GetState() != BRICK_STATE_TOUCHED)
					{
						brick->SetState(BRICK_STATE_TOUCHED);
					}
				}
				else if (dynamic_cast<CGoomBa*>(objects[i]))
				{
					CGoomBa* goomba = dynamic_cast<CGoomBa*>(objects[i]);
					if (goomba->GetState() != GOOMBA_STATE_DIE_WITH_DEFLECT)
					{
						if (goomba->GetLevel() == GOOMBA_LEVEL_2)
						{
							goomba->SetLevel(GOOMBA_LEVEL_1);
						}
						goomba->SetState(GOOMBA_STATE_DIE_WITH_DEFLECT);
						goomba->vy = -GOOMBA_DEFLECT_SPEED;
						goomba->ny = -1;
					}
				}
				else if (dynamic_cast<CKoopas*>(objects[i]))
				{
					CKoopas* koopa = dynamic_cast<CKoopas*>(objects[i]);
					if (koopa->isOnGround)
					{
						koopa->AttackedByTail();
					}
				}
				else if (dynamic_cast<CRedVenusFireTrap*> (objects[i]))
				{
					CRedVenusFireTrap* venus = dynamic_cast<CRedVenusFireTrap*>(objects[i]);
					venus->SetAttackedAnimation(AttackedBy::Tail,Points::NONE);
					venus->isEnable = false;
				}
			}
		
		}
	}


}

void CMarioTail::Render()
{
	//RenderBoundingBox();
}

void CMarioTail::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + MARIO_TAIL_BBOX;
	b = y + MARIO_TAIL_BBOX;
}
