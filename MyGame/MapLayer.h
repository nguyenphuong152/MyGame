#pragma once
#include "tinyxml.h"
#include <vector>
#include <Windows.h>

#define MAX_MAP_SIZE	200

#define CAM_WIDTH	764
#define CAM_HEIGHT	760


class CMapLayer {

	const char* mapInfo;
	float width, height;
	
	int tileset[MAX_MAP_SIZE][MAX_MAP_SIZE];

	void SetRenderRegion(int &cell_startX, int &cell_startY, int &cell_endX, int &cell_endY);
public:
	CMapLayer(TiXmlElement* layer, float width, float height);
	void RenderLayer();
};
