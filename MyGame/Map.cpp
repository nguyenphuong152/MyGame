#include "Map.h"
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "tinyxml.h"
#include "TileSet.h"


using namespace std;

#define TILE_WIDTH 48


CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::AddMap(int id, const char* mapFilePath, int mapWidth, int mapHeight, int texId, int tilePerRow, int tilePerColumn)
{
	this->id = id;
	this->mapFilePath = mapFilePath;
	this->mapWidth = mapWidth;
	this->mapHeight = mapHeight;
	this->texId = texId;
	this->tilePerRow = tilePerRow;
	this->tilePerColumn = tilePerColumn;
}

void CMap::CreateTileSet()
{
	//cut tileset
	int idd = 1;
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
			//DebugOut(L"[INFO] map added: %d, %d, %d, %d, %d \n", idd, l, t, r, b);
			idd++;
		}
	}
}


void CMap::HandleMap()
{	
	TiXmlDocument doc(mapFilePath);
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERR] Load tmx file failed \n");
		return ;
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* layer = nullptr;

	for (layer = root->FirstChildElement(); layer != NULL; layer = layer->NextSiblingElement())
	{
		string name = layer->FirstChildElement()->Value();
		if (name == "data")
		{
			CMapLayer* tileset = new CMapLayer(layer->FirstChildElement());
			layers.push_back(tileset);
		}
	}
}

