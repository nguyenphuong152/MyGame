#pragma once

#include <d3dx9.h>
#include "MapLayer.h"
#include "Utils.h"
#include "GameObject.h"

typedef CMapLayer* LPLAYERS;

class CMap
{
protected:
	int id;
	const char*  mapFilePath;
	int texId;
	int tilePerRow, tilePerColumn;

	std::vector<LPLAYERS> layers ;

	CMapLayer* layerForeground;
	
public:
	CMap(int id, const char*  mapFilePath, int texId,int tilePerRow, int TilePerColumn);
	void CreateTileSet();
	void HandleMap();
	void RenderMap();
	void RenderForeground();
};


