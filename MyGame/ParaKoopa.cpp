#include "ParaKoopa.h"
#include "Ground.h"
#include "Box.h"
#include "Utils.h"
#include "Grid.h"
#include "Boundary.h"

CParaKoopa::CParaKoopa()
{
	nx = -1;
	ny = 1;
	vx = KOOPA_WALKING_SPEED*nx;
	SetLevel(KOOPA_LEVEL_2);
	SetState(PARA_KOOPA_STATE_JUMPING);
}

void CParaKoopa::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	CKoopas::GetBoundingBox(l, t, r, b);
}

void CParaKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (GetLevel() == KOOPA_LEVEL_2)
	{
		CEnemy::Update(dt, coObjects);
		vy += PARA_KOOPA_GRAVITY * dt;

		if (isOnGround) SetState(PARA_KOOPA_STATE_JUMPING);

		//collision logic with other objects
		HandleCollision(coEventsResult);

		ClearCoEvents();
		grid_->Move(this);
	}
	else
	{
		CKoopas::Update(dt, coObjects);
	}
}

void CParaKoopa::Render()
{
	int ani = -1;
	if (GetLevel()==KOOPA_LEVEL_2)
	{
		ani = PARA_KOOPA_ANI_JUMPING;
		animation_set->at(ani)->Render(0,ny, x, y);
	}
	else
	{
		CKoopas::Render();
	}
	//RenderBoundingBox();
}

void CParaKoopa::HandleCollision(vector<LPCOLLISIONEVENT> coEventRe)
{
	for (UINT i = 0; i < coEventsResult.size(); i++)
	{
		LPCOLLISIONEVENT e = coEventsResult[i];

		if (dynamic_cast<CGround*>(e->obj) || dynamic_cast<CBox*>(e->obj))
		{
			if (e->ny < 0)
			{
				isOnGround = true;
			}
		}
		else if (dynamic_cast<CBoundary*>(e->obj))
		{
			isEnable = false;
		}
	}
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	if (GetLevel() == KOOPA_LEVEL_2)
	{
		isOnGround = false;
		vy = -PARA_KOOPA_HIGH_JUMP_VELOCITY_Y;
	}
	else {
		CKoopas::SetState(state);
	}

}