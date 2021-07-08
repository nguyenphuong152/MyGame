#pragma once
#include "GameObject.h"
#include "Unit.h"

class CMapObjects
{
	static CMapObjects* __instance;
public:
	void GenerateObject(const char* mapFilePath, vector<LPGAMEOBJECT>& objects);
	static CMapObjects* GetInstance();
};