#pragma once
#include "GameObject.h"
#include "Grid.h"

class CMapObjects
{
	Grid* grid;
public:
	CMapObjects(Grid* g);
	void GenerateObject(const char* mapFilePath, vector<LPGAMEOBJECT>& objects);
};