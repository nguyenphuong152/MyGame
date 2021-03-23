#pragma once

#include <d3dx9.h>
#include "MapLayer.h"

typedef CMapLayer* MAP_LAYERS;

class CMap
{
	static CMap* __instance;
protected:
	int id;
	const char*  mapFilePath;
	int mapWidth, mapHeight, texId;
	int tilePerRow, tilePerColumn;

	vector<MAP_LAYERS> layers ;
public:
	void AddMap(int id, const char*  mapFilePath, int mapWidth, int mapHeight, int texId,int tilePerRow, int TilePerColumn);
	void CreateTileSet();
	void HandleMap();
	void RenderMap();

	static CMap* GetInstance();
};


