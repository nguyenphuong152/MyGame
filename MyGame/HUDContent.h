#pragma once
#include "Text.h"
#include "Mario.h"

class HUDContent {
	static HUDContent* __instance;
	CText* world;
	CText* live;
	CText* point;
	CText* time;
	CText* coin;
	CText* power;

	CMario* player;

public:
	static HUDContent* GetInstance();
	void Render();
	void Update();
	void SetUpContent();
	void SetUpPlayer(CMario* mario) { player = mario; };
};