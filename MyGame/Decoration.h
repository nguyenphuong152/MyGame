#pragma once
#include "GameObject.h" 

#define ENEMY_WALKING_SPEED	0.05f

#define NUMBER_1 99991	
#define NUMBER_4 99994

#define SHOWING_TIME 1500

#define NUMBER_1_POS_X	440
#define NUMBER_1_POS_Y 220

#define NUMBER_2_POS_X 510
#define NUMBER_2_POS_Y 285

enum class Type {
	Tree,
	Help,
	M,
	Enemy,
	Dialog
};

class CDecoration : public CGameObject
{
	int dir;
	Type type;

	ULONGLONG showing_start;

	void StartShowing() { showing_start = GetTickCount64(); };
public:
	CDecoration(Type type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject);
};