#pragma once
#include "GameObject.h"

#define CAM_WIDTH   760
#define CAM_HEIGHT	600

#define NUM_CELL	200

#define CELL_SIZE	480

class Grid {
	LPGAMEOBJECT cells[NUM_CELL][NUM_CELL] ;
public:
	Grid();
	void Add(LPGAMEOBJECT obj);

	void Update(DWORD dt, vector<LPGAMEOBJECT> *coObjs);
	void Render();

	void Move(LPGAMEOBJECT object);

	void GetActiveRegion(int& cell_startX, int& cell_startY, int& cell_endX, int& cell_endY);
	void GetUnitsFromCameraRegion(vector<LPGAMEOBJECT>* objs);
};