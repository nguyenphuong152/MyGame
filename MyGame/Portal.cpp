#include "Portal.h"

CPortal::CPortal(int texture, int scene_id)
{
	this->scene_id = scene_id;
	this->texture = texture;
	isEnable = true;
}

void CPortal::Render()
{
	CSprites::GetInstance()->Get(texture)->Draw(-1, 1, x, y);
	RenderBoundingBox();
}

void CPortal::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x;
	t = y;
	r = x + PORTAL_BBOX;
	b = y + PORTAL_BBOX;
}