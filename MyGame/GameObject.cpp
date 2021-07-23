#include <d3dx9.h>
#include <algorithm>

#include "Utils.h"
#include "Game.h"
#include "GameObject.h"
#include "Sprites.h"
#include "Textures.h"
#include "FireBallPool.h"
#include "Grid.h"
#include "Coin.h"
#include "BreakableBrick.h"
#include "PowerUp.h"
#include "One-upMushroom.h"
CGameObject::CGameObject()
{
	x = y = old_x = old_y = 0;
	vx = vy = 0;
	nx = 1;
}

void CGameObject::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	SetOldPosition(x, y);

	this->dt = dt;
	dx = vx * dt;
	dy = vy * dt;
}

/*
	Extension of original SweptAABB to deal with two moving objects
*/

LPCOLLISIONEVENT CGameObject::SweptAABBEx(LPGAMEOBJECT coO)
{
	float sl, st, sr, sb;
	float ml, mt, mr, mb;
	float nx, ny, t;

	coO->GetBoundingBox(sl, st, sr, sb);

	// deal with moving object: m speed = original m speed - collide object speed
	float svx, svy; //get van toc cua static obj
	coO->GetSpeed(svx, svy);

	//quang duong da di of static obje
	float sdx = svx * dt;
	float sdy = svy * dt;

	// (rdx, rdy) is RELATIVE movement distance/velocity 
	float rdx = this->dx - sdx; //quang duong can phai di de co collide
	float rdy = this->dy - sdy;

	GetBoundingBox(ml, mt, mr, mb); //doi tuong duoc truyen vao la static, thg dg goi ham nay la thg moving

	CGame::SweptAABB(
		ml, mt, mr, mb,
		rdx, rdy,
		sl, st, sr, sb,
		t, nx, ny
	);

	CCollisionEvent* e = new CCollisionEvent(t, nx, ny, rdx, rdy, coO);
	return e;
}

/*
	Calculate potential collisions with the list of colliable objects

	coObjects: the list of colliable objects
	coEvents: list of potential collisions
*/

void CGameObject::CalcPotentialCollisions(
	vector<LPGAMEOBJECT>* coObjects, vector<LPCOLLISIONEVENT>& coEvents)
{
	for (UINT i = 0;i < coObjects->size();i++)
	{
		LPCOLLISIONEVENT e = SweptAABBEx(coObjects->at(i));

		if (e->t > 0 && e->t <= 1.0f)
			coEvents.push_back(e);
		else
			delete e;
		
	}

	std::sort(coEvents.begin(), coEvents.end(), CCollisionEvent::compare);
}

//flow :: 1 doi tuong game object goi CalpotentialColli->xet sweept aabbex++aabb cua thg goi cal voi thg dc truyen vao-

void CGameObject::FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coEventsResult, float& nx, float& ny )
{
	float min_tx = 1.0f;
	float min_ty = 1.0f;
	int min_ix = -1;
	int min_iy = -1;

	nx = 0.0f;
	ny = 0.0f;

	coEventsResult.clear();

	LPGAMEOBJECT objx = NULL;
	LPGAMEOBJECT objy = NULL;

	for (UINT i = 0; i < coEvents.size(); i++)
	{
		LPCOLLISIONEVENT c = coEvents[i];
		if (c->nx != 0)
		{
			bool hasObjx = false;
			if (objx != NULL && c->obj != NULL)
			{
				if (c->obj->y < objx->y) hasObjx = true;
			}

			if (c->t < min_tx || (c->t==min_tx && hasObjx))
			{
				min_tx = c->t; nx = c->nx; min_ix = i;
				objx = c->obj;
			}
		}

		if (c->t < min_ty && c->ny != 0)
		{
			min_ty = c->t; ny = c->ny; min_iy = i;
		}

	}

	//neu va cham voi obj ma do gravity nen va cham theo hai chieu, skip chieu x va k push vao coEvents result
	if (objx != NULL && objy != NULL && objx->y == objy->y)
	{
		min_tx = 1.0f;
		nx = 0;
	}
	else if (min_ix >= 0) coEventsResult.push_back(coEvents[min_ix]);

	if (min_iy >= 0) coEventsResult.push_back(coEvents[min_iy]);

	BlockObject(objx, objy, min_tx, min_ty, nx, ny);
}


void CGameObject::BlockObject( LPGAMEOBJECT objx, LPGAMEOBJECT objy,float min_tx, float min_ty, float nx, float ny)
{
	if (objx != NULL)
	{
		bool coinBrick = false;
		if (dynamic_cast<CBreakableBrick*>(objx))
		{
			CBreakableBrick* b = dynamic_cast<CBreakableBrick*>(objx);
			if (b->state == BREAKABLE_BRICK_COIN_STATE) coinBrick = true;
		}
		if (dynamic_cast<CCoin*>(objx) || dynamic_cast<CPowerUp*>(objx)
			|| dynamic_cast<COneUpMushroom*>(objx)
			|| coinBrick == true)
		{
			x = x;
		}
	}
	else {
		x += min_tx * dx + nx * 0.4f;
		if (nx != 0) vx = 0;
	}

	if (objy != NULL)
	{
		bool coinBrick = false;
		if (dynamic_cast<CBreakableBrick*>(objy))
		{
			CBreakableBrick* b = dynamic_cast<CBreakableBrick*>(objy);
			if (b->state == BREAKABLE_BRICK_COIN_STATE) coinBrick = true;
		}
		if (dynamic_cast<CCoin*>(objy) || dynamic_cast<CPowerUp*>(objy)
			|| dynamic_cast<COneUpMushroom*>(objy) || coinBrick == true)
		{
			y = y;
		}
	}
	else {
		y += min_ty * dy + ny * 0.4f;
		if (ny != 0) vy = 0;
	}
}


RECT CGameObject::CalculateRect()
{
	RECT rect;

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	return rect;
}


void CGameObject::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	RECT rect = CalculateRect();

	CGame::GetInstance()->Draw(0,0,x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 32);
}

bool CGameObject::AABB(CGameObject* object)
{
	float left_a, right_a, top_a, bottom_a, left_b, right_b, top_b, bottom_b;

	GetBoundingBox(left_a, top_a, right_a, bottom_a);
	object->GetBoundingBox(left_b, top_b, right_b, bottom_b);
	if (left_a < right_b && right_a > left_b && top_a < bottom_b && bottom_a > top_b)
		return true;
	return false;
}

void CGameObject::AddObjectToGrid(Grid* grid, int id)
{
	//DebugOut(L"%d \n",id);
	grid_ = grid;
	grid_->Add(this, id);
}

void CGameObject::SetAnimation(int ani)
{
	CAnimationSets* animation_sets = CAnimationSets::GetInstance();
	LPANIMATION_SET ani_set = animation_sets->Get(ani);
	SetAnimationSet(ani_set);
}

CGameObject::~CGameObject()
{

}

