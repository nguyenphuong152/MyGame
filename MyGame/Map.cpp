#include "Map.h"
#include <fstream>
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"

using namespace std;

#define TILE_WITDH 64


CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::AddMap(int idMap, LPCWSTR filePath, int witdh, int height, int textureID)
{
	this->id = idMap;
	this->mapFilePath = filePath;
	this->mapWidth = witdh;
	this->mapHeight = height;
	this->texId = textureID;
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

	int id = 0;

	for (int i = 0;i < 7;i++)
	{		
		for (int j = 0;j < 20;j++)
		{
			
			int t = i * TILE_WITDH;
			int l = j * TILE_WITDH;
			int r = l + TILE_WITDH;
			int b = t + TILE_WITDH;

			LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);
			CSprites::GetInstance()->Add(id, l, t, r, b, tex);
			DebugOut(L"[INFO] map added: %d, %d, %d, %d, %d \n", id, l, t, r, b);
			id++;
		}
	}	
}


void CMap::RenderMap()
{
	
	for (int i = 0; i < mapHeight;i++)
	{
		for (int j = 0;j < mapWidth ;j++)
		{
			CSprites::GetInstance()->Get(tileMap[i][j])->Draw(j*TILE_WITDH, i*TILE_WITDH);
		}

	}
}

