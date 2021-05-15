#include "HUD.h"
#include <cstddef>
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "Utils.h"
#include "Camera.h"
#include "HUDContent.h"

HUD* HUD::__instance = NULL;

HUD* HUD::GetInstance()
{
	if (__instance == NULL) __instance = new HUD();
	return __instance;
}

void HUD::Render()
{
	RenderBoundingBox();
	CSprites::GetInstance()->Get(HUD_texture)->Draw(-1, 1, x, y);
	HUDContent::GetInstance()->Render();

}

void HUD::SetPosition()
{
	CCamera* camera = CCamera::GetInstance();
	x = floor(camera->x);
	y = floor(camera->y+HUD_POSTION_Y);

}

void HUD::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPDIRECT3DTEXTURE9 bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	l = x;
	t = y;
	r = x + HUD_WIDTH;
	b = y + HUD_HEIGHT;

	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(0, 0, x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void HUD::Init(int texture)
{
	this->HUD_texture = texture;
	HUDContent::GetInstance()->SetUpContent();
}

void HUD::Update()
{
	SetPosition();
	HUDContent::GetInstance()->Update();
}

void HUD::AddLetter(string name, int texture)
{
	letters[name] = texture;
}
