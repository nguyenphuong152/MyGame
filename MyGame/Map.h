#include <d3dx9.h>

#define MAX_MAP_WITDH 100
#define MAX_MAP_HEIGHT 100

class CMap
{
	static CMap* __instance;

protected:
	int id;
	LPCWSTR mapFilePath;
	int mapWidth, mapHeight, texId;
	int tileMap[MAX_MAP_WITDH][MAX_MAP_HEIGHT];

public:
	//CMap();
	//CMap(int id, LPCWSTR mapFilePath,int mapWidth, int mapHeight, int texId);
	void AddMap(int id, LPCWSTR mapFilePath, int mapWidth, int mapHeight, int texId);
	void LoadMap();
	void RenderMap();

	static CMap* GetInstance();
};

typedef CMap* LPMAP;

