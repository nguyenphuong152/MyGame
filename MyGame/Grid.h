#pragma once
#include <vector>
#include "Unit.h"

#define CAM_WIDTH	764
#define CAM_HEIGHT	760

using namespace std;

class Grid {
	int cell_width;
	int cell_height;

	int rows;
	int cols;

	vector<vector<LPUNIT>> cells;
public:
	Grid(int  map_width, int map_height, int cell_width, int cell_height);
	void Add(Unit* unit);
	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjs);
	void Move(Unit* unit, float x, float y);
	void HandleCell(Unit* cell,DWORD dt, vector<LPGAMEOBJECT> *coObjs);
	void GetUnitsFromCameraRegion(vector<LPUNIT>* units);
};