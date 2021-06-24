#pragma once
#include "GameObject.h"
#include "Mario.h"

class CMapObjects
{
	static CMapObjects* __instance;
public:
	void GenerateObject(const char* mapFilePath, vector<LPGAMEOBJECT>& objects,CMario* mario);
	static CMapObjects* GetInstance();
};