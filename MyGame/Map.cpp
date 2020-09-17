#include "Map.h"
#include <fstream>
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"


//using namespace std;

#define TILE_WIDTH 64


CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::AddMap(int id, LPCWSTR mapFilePath, int mapWidth, int mapHeight, int texId, int tilePerRow, int tilePerColumn)
{
	this->id = id;
	this->mapFilePath = mapFilePath;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->texId = texId;
	this->tilePerRow = tilePerRow;
	this->tilePerColumn = tilePerColumn;
}

void CMap::LoadMap()
{
	ifstream file;
	file.open(mapFilePath);

	if (!file) {
		DebugOut(L"[ERROR] Failed to read map : %s \n", mapFilePath);
		exit(1);   // call system to stop
	}

	for (int i = 0; i < mapHeight;i++)
	{
		for (int j = 0;j < mapWidth;j++)
		{
			file >> tileMap[i][j];
		}
	}
	file.close();

	int idd = 0;
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);

	for (int i = 0;i < tilePerColumn;i++)
	{		
		for (int j = 0;j < tilePerRow;j++)
		{
			
			int t = i * TILE_WIDTH;
			int l = j * TILE_WIDTH;
			int r = l + TILE_WIDTH;
			int b = t + TILE_WIDTH;

			CSprites::GetInstance()->Add(idd, l, t, r, b, tex);
		//	DebugOut(L"[INFO] map added: %d, %d, %d, %d, %d \n", id, l, t, r, b);
			idd++;
		}
	}	
}


void CMap::RenderMap()
{
	for (int i = 0; i < mapHeight;i++)
	{
		for (int j = 0;j <mapWidth;j++)
		{	
			CSprites::GetInstance()->Get(tileMap[i][j])->Draw(0,j * TILE_WIDTH, i * TILE_WIDTH);
			//DebugOut(L"[INFO] draw added: %d, %d, %d\n", a,b,c);	
		}

	}
}

