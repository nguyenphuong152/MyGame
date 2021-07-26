#pragma once
#include "GameObject.h"
#include <unordered_set>

class Cell {

	unordered_set<LPGAMEOBJECT> objects;
public:
	void AddObjectToCell(LPGAMEOBJECT obj);
	void RemoveObjectInCell(LPGAMEOBJECT obj);
	vector<LPGAMEOBJECT> GetListObjectInCell();
	void Update(DWORD dt, vector<LPGAMEOBJECT>*  coObj);
	void Render();
};