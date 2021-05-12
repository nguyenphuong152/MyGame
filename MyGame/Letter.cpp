#include "Letter.h"
#include "Sprites.h"
#include "HUD.h"

CLetter::CLetter(string name, int texture)
{
	this->name = name;
	this->texture = texture;
}
void CLetter::Render()
{
	CSprites::GetInstance()->Get(texture)->Draw(-1, 1, x, y);
}

void CLetter::SetPosition(float x, float y)
{
	HUD* hud = HUD::GetInstance();
	float hud_x, hud_y;
	hud->GetPosition(hud_x, hud_y);
	this->x = hud_x +x;
	this->y = hud_y +y;
}