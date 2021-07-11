#pragma once
#include <string>
#include <unordered_map>
#include "Utils.h"
#include "Mario.h"
#include "HUDContent.h"

using namespace std;

#define HUD_WIDTH	760
#define HUD_HEIGHT	200

#define HUD_POSITION_Y	550
#define HUD_POSITION_Y_OW	600

#define HUD_ALIGN_TOP		22
#define HUD_ALIGN_BOTTOM	48 
#define HUD_ALIGN_RIGHT		378
#define HUD_ALIGN_LEFT		115 
#define HUD_BLANKSPACE		24

class HUD {
	float x,y;
	float position_y;

	int countdown_start = GetTickCount64();
	/*CMario* player;
	*/

	unordered_map<string, int> letters;
	int hud_texture;

	static HUD* __instance;

public:
	static HUD* GetInstance();

	void AddLetter(string name, int texture);
	int GetTextureOfLetter(string name) { return letters[name]; };

	void Init(int texture, float pos_hud);
	void GetPosition(float& x, float& y) { x = this->x; y = this->y; };
	
	void SetPosition(float pos_hud);

	void Render();
	void RenderBoundingBox();

	void Unload();
	
	void Update();
	void UpdatePosition();
	
	//void StartCountdown() { countdown_start = GetTickCount64(); };
	int GetCountdownStart() { return countdown_start; };
};