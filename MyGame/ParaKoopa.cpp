#include "ParaKoopa.h"
#include "Ground.h"
#include "Box.h"
#include "Utils.h"

CParaKoopa::CParaKoopa()
{
	isEnable = true;
	nx = -1;
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
		CGameObject::Update(dt, coObjects);
		vy += PARA_KOOPA_GRAVITY * dt;

		if (isOnGround) SetState(PARA_KOOPA_STATE_JUMPING);

		vector<LPCOLLISIONEVENT> coEvents;
		vector<LPCOLLISIONEVENT> coEventsResult;

		coEvents.clear();

		CalcPotentialCollisions(coObjects, coEvents);

		if (coEvents.size() == 0)
		{
			x += dx;
			y += dy;
		}
		else
		{
			float min_tx, min_ty, nx = 0, ny = 0;

			float rdx = 0, rdy = 0;

			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny, rdx, rdy);

			//day object ra mot khoang de k bi chong va cham
			x += min_tx * dx + nx * 0.4f;

			if (nx != 0) vx = 0;
			if (ny != 0) vy = 0;

			//collision logic with other objects
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
			}
		}

		for (UINT i = 0; i < coEvents.size(); i++) delete coEvents[i];
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
		animation_set->at(ani)->Render(0,0, x, y);
	}
	else
	{
		CKoopas::Render();
	}
	//RenderBoundingBox();
}

void CParaKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	if (GetLevel() == KOOPA_LEVEL_2)
	{
		isOnGround = false;
		vy = -HIGH_JUMP_VELOCITY_Y;
	}
	else {
		CKoopas::SetState(state);
	}

}