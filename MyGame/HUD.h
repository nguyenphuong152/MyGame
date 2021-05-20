#pragma once
#include <string>
#include <unordered_map>
#include "Utils.h"

using namespace std;

#define HUD_WIDTH	766
#define HUD_HEIGHT	88

#define HUD_POSTION_Y	636

#define HUD_ALIGN_TOP		22
#define HUD_ALIGN_BOTTOM	48 
#define HUD_ALIGN_RIGHT		378
#define HUD_ALIGN_LEFT		115 
#define HUD_BLANKSPACE		24

class HUD {
	float x,y;
	float position_y;

	int HUD_texture;

	static HUD* __instance;
	unordered_map<string, int> letters;

	int countdown_start = GetTickCount64();

public:

	static HUD* GetInstance();
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; };
	
	void Init(int texture);
	void SetPosition(float pos_hud);

	void Render();
	void RenderBoundingBox();
	
	void Update();
	void UpdatePosition();
	void AddLetter(string name, int texture);
	int GetTextureOfLetter(string name) { return letters[name]; };
	
	void StartCountdown() { countdown_start = GetTickCount64(); };
	int GetCountdownStart() { return countdown_start; };

};