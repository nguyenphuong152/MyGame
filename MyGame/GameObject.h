#pragma once
#include <Windows.h>
#include <d3dx9.h>
#include <vector>

#include "Sprites.h"
#include "Animations.h"


using namespace std;

#define ID_TEX_BBOX -100

class CGameObject;
typedef CGameObject* LPGAMEOBJECT;

struct CCollisionEvent;
typedef CCollisionEvent* LPCOLLISIONEVENT;

struct CCollisionEvent
{
	LPGAMEOBJECT obj;
	float t, nx, ny;

	//bool collide_x, collide_y;

	float dx, dy; //// *RELATIVE* movement distance between this object and obj

	CCollisionEvent(float t, float nx, float ny, float dx = 0, float dy = 0, LPGAMEOBJECT obj = NULL)
	{
		this->t = t;
		this->nx = nx;
		this->ny = ny;
		this->dx = dx;
		this->dy = dy;
		this->obj = obj;
	}

	static bool compare(LPCOLLISIONEVENT& a, LPCOLLISIONEVENT& b) //sao co &
	{
		return a->t < b->t;
	}
};


class CGameObject
{
	friend class Grid;
protected:
	Grid* grid_;
public:
	//vi tri
	float x;
	float y;

    //old postition
	float old_x;
	float old_y;

	//van toc
	float vx;
	float vy;

	//quang duong
	float dx;   //dx = vx*dt
	float dy;

	int nx; //huong; 
	int ny;
	//nx = 1 => left
	//nx = -1 => right

	int state; // trang thai

	DWORD dt; //time

	bool isEnable = false;
	bool isDie = false;
	
	LPANIMATION_SET animation_set;

public:
	void SetOldPosition(float x, float y) { this->old_x = x; this->old_y = y; };
	void SetPosition(float x, float y) { this->x = x; this->y = y; }
	void SetSpeed(float vx, float vy) { this->vx = vx; this->vy = vy; }
	
	void GetOldPosition(float& x, float& y) { x = this->old_x; y = this->old_y; }
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; }
	void GetSpeed(float& vx, float& vy) { vx = this->vx, vy = this->vy; }

	int GetState() { return this->state; }

	RECT CalculateRect();
	void RenderBoundingBox();

	void SetAnimationSet(LPANIMATION_SET ani_set) { animation_set = ani_set; }

	//extension of aabb, xet 2 vat dg di chuyen, 1 vat duoc xem la dung yen
	LPCOLLISIONEVENT SweptAABBEx(LPGAMEOBJECT coO);

	//aabb xét vật tĩnh đụng nhau
	bool AABB(CGameObject* object);

	void AddObjectToGrid(Grid* grid, int id);

	void SetObjectAnimation(int ani);

	void CalcPotentialCollisions(vector<LPGAMEOBJECT>* coObject, vector<LPCOLLISIONEVENT>& coEvents);;

	void FilterCollision(vector<LPCOLLISIONEVENT>& coEvents, vector<LPCOLLISIONEVENT>& coResults, float& nx, float& ny);

	void BlockObject(LPGAMEOBJECT objx, LPGAMEOBJECT objy, float min_tx, float min_ty, float nx, float ny);

	CGameObject();

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b) = 0;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects = NULL);
	virtual void Render() = 0;
	virtual void SetState(int state) { this->state = state; }

	~CGameObject();
};