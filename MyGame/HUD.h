#pragma once
#include "Camera.h"

#define HUD_WIDTH	765
#define HUD_HEIGHT	86

#define HUD_POSTION_Y	636

class HUD {
	float x,y;

	int HUD_texture;
	string world_order;
	static HUD* __instance;
public:
	static HUD* GetInstance();
	void SetTexture(int texture) { this->HUD_texture = texture; };
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; };
	void SetPosition();
	void SetWorldOrder();
	void SetMarioLifeNumber();
	void Render();
	void Update();
	void RenderWorldOrder();
	void RenderMarioLife();
	void RenderBoundingBox();
};