#pragma once
#include "GameObject.h"

class CMarioTail : public CGameObject
{
	public:
		CMarioTail();
		virtual void Render();
		virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
		virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
};