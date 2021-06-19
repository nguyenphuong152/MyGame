#pragma once
#include "GameObject.h"

class CMario;

#define MARIO_TAIL_BBOX 30

class CMarioTail : public CGameObject
{
	CMario* player;
	public:
		CMarioTail(CMario* mario);
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
		void Update(vector<LPGAMEOBJECT> objects);
};