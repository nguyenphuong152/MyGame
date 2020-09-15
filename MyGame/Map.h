#include <d3dx9.h>

#define MAX_MAP_WITDH 50
#define MAX_MAP_HEIGHT 50

class CMap
{
	static CMap* __instance;
protected:
	int id;
	LPCWSTR mapFilePath;
	int mapWidth, mapHeight, texId;
	int tilePerRow, tilePerColumn;
	int tileMap[MAX_MAP_WITDH][MAX_MAP_HEIGHT];

public:
	void AddMap(int id, LPCWSTR mapFilePath, int mapWidth, int mapHeight, int texId,int tilePerRow, int TilePerColumn);
	void LoadMap();
	void RenderMap();

	static CMap* GetInstance();
};


