#pragma once
#include "GameObject.h"

#define MARIO_TAIL_BBOX 30

class CMarioTail : public CGameObject
{
	public:
		CMarioTail();
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
		void Update(vector<LPGAMEOBJECT> objects);
};