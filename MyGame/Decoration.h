#pragma once
#include "GameObject.h" 

#define ENEMY_WALKING_SPEED	0.05f

enum class Type {
	Tree,
	Help,
	M,
	Enemy
};

class CDecoration : public CGameObject
{
	int dir;
	Type type;
public:
	CDecoration(Type type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
};