#pragma once
#include "tinyxml.h"
#include <vector>
#include <Windows.h>

#define MAPWIDTH 176
#define MAPHEIGHT 41

#define MAPWORLD_HEIGHT	14
#define MAPWORLD_WIDTH	16

#define MAPWIDTH1_3 158
#define MAPHEIGHT1_3	50


class CMapLayer {

	const char* mapInfo;
	std::vector<int> tileIdSet;

public:
	CMapLayer(TiXmlElement* layer);
	void RenderLayer();
	void SetWidthHeight(float& width, float& height);
};
