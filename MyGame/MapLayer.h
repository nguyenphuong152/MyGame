#pragma once
#include "tinyxml.h"
#include <vector>
#include <Windows.h>

#define MAPWIDTH 176
#define MAPHEIGHT 41

class CMapLayer {

	const char* mapInfo;
	std::vector<int> tileIdSet;

public:
	CMapLayer(TiXmlElement* layer);
	void RenderLayer();
};
