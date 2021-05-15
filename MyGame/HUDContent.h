#pragma once
#include "Text.h"

class HUDContent {
	static HUDContent* __instance;
	CText* world;
	CText* live;
	CText* point;
	CText* time;
public:
	static HUDContent* GetInstance();
	void Render();
	void Update();
	void SetUpContent();
};