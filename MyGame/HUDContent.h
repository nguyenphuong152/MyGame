#pragma once
#include "Text.h"


class HUDContent {
	CText* world;
	CText* live;
	CText* point;
	CText* time;
	CText* coin;
	CText* power;
	CMario* player;

	static HUDContent* __instance;

public:
	static HUDContent* GetInstance();

	void Unload();
	void Render();
	void Update();
	void SetUpContent();
};