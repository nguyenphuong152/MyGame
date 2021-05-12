#include "HUD.h"
#include <cstddef>
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "LetterManager.h"

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
	RenderWorldOrder();
}

void HUD::SetPosition()
{
	CCamera* camera = CCamera::GetInstance();
	x = camera->x;
	y = camera->y+HUD_POSTION_Y;
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


void HUD::SetWorldOrder()
{
	world_order = "1";
	CLetterManager::GetInstance()->GetLetterTexture(world_order)->SetPosition(110,25);
}

void HUD::RenderWorldOrder()
{
	CLetterManager::GetInstance()->GetLetterTexture(world_order)->Render();
}

void HUD::Update()
{
	SetPosition();
	SetWorldOrder();
}