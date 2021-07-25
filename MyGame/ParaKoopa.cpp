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
		vx = KOOPA_WALKING_SPEED * nx;
		if (isOnGround) SetState(PARA_KOOPA_STATE_JUMPING);
	}
	CKoopas::Update(dt, coObjects);
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


void CParaKoopa::SetState(int state)
{
	if (GetLevel() == KOOPA_LEVEL_2)
	{
		isOnGround = false;
		vy = -PARA_KOOPA_HIGH_JUMP_VELOCITY_Y;
	}
	CKoopas::SetState(state);

}