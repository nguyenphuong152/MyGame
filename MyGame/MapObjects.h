#pragma once
#include "GameObject.h"


class CMapObjects
{
	static CMapObjects* __instance;
public:
	void GenerateObject(const char* mapFilePath, vector<LPGAMEOBJECT>& objects);
	static CMapObjects* GetInstance();
};