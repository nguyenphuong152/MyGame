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

void HUD::Init(int texture, float pos_hud)
{
	rewards.clear();
	SetPosition(pos_hud);
	hud_texture = texture;
	HUDContent::GetInstance()->SetUpContent();
}

void HUD::AddReward(reward type)
{
	Reward* r = new Reward(type);
	float hx, hy;
	GetPosition(hx, hy);
	r->SetPosition((float)hx+REWARD_ALIGN_LEFT * (rewards.size()+1), (float) hy+HUD_ALIGN_TOP-4);
	rewards.push_back(r);
}

void HUD::Render()
{
	RenderBoundingBox();
	if (CGame::GetInstance()->current_scene != OVERWORLD_MAP)
	{
		CSprites::GetInstance()->Get(hud_texture)->Draw(-1, 1, x, y);
	}
	else {
		CSprites::GetInstance()->Get(hud_texture)->Draw(-1, 1, x+30, y);
	}
	HUDContent::GetInstance()->Render();

	for (UINT i = 0; i < rewards.size(); i++)
		rewards[i]->Render();
}

void HUD::SetPosition(float pos_hud)
{
	position_y = pos_hud;
	CCamera* camera = CGame::GetInstance()->GetMainCamera();
	x = floor(camera->x);
	y = floor(camera->y+ pos_hud);

	for (UINT i = 0; i < rewards.size(); i++)
	{
		rewards[i]->SetPosition((float)(x + REWARD_ALIGN_LEFT * (rewards.size() + 1)), (float)(y + HUD_ALIGN_TOP - 4));
	}	

}

void HUD::UpdatePosition()
{
	CCamera* camera = CGame::GetInstance()->GetMainCamera();
	x = floor(camera->x);
	y = floor(camera->y + position_y);
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
	rect.top = -0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	CGame::GetInstance()->Draw(0, 0, x, y, bbox, rect.left, rect.top, rect.right, rect.bottom, 255);
}

void HUD::Unload()
{
	hud_texture = -1;
	HUDContent::GetInstance()->Unload();
}

void HUD::AddLetter(string name, int texture)
{
	letters[name] = texture;
}


void HUD::Update()
{
	UpdatePosition();
	HUDContent::GetInstance()->Update();

	for (UINT i = 0; i < rewards.size(); i++)
		rewards[i]->Update();
}
