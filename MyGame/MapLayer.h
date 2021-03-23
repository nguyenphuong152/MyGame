#pragma once
#include "tinyxml.h"

#define TILEPERROW 176
#define TILEPERCOLUMN	41

class CMapLayer {

	static CMapLayer* __instance;
	const char* mapInfo;
public:
	CMapLayer(TiXmlElement* layer);
	void RenderLayer();

	static CMapLayer* GetInstance();
};
