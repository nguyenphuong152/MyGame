#include "Arrow.h"

CArrow::CArrow()
{
	start_y = 0;
	startGame = false;
	isEnable = true;
	SetObjectAnimation(ARROW_ANI);
}

void CArrow::MoveUp()
{
	y = start_y;
}

void CArrow::MoveDown()
{
	y = start_y + 55;
}

void CArrow::StartGame()
{
	if (y == start_y) startGame = true;
}



void CArrow::Render()
{
	animation_set->at(0)->Render(-1, 1, x, y);
}

void CArrow::Update(DWORD dt, vector<LPGAMEOBJECT>* colObjects)
{
	CGameObject::Update(dt);
}

void CArrow::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}
