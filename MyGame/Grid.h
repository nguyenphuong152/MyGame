#pragma once
#include "GameObject.h"
#include "Cell.h"

#define NUM_CELL	200

#define CELL_SIZE	400

class Grid {
	Cell* cells[NUM_CELL][NUM_CELL] ;
	unordered_map<int, D3DXVECTOR4> grid_objs;
	void UpdatePool(vector<LPGAMEOBJECT>* cobjects, DWORD dt);
public:
	Grid();
	void Add(LPGAMEOBJECT obj, int id);

	void ReadFile(const char* mapFilePath);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjs);
	void Render();

	void Move(LPGAMEOBJECT object);

	void Unload();

	void GetActiveRegion(int& cell_startX, int& cell_startY, int& cell_endX, int& cell_endY);
	void GetUnitsFromCameraRegion(vector<LPGAMEOBJECT>* objs);

	~Grid();
};