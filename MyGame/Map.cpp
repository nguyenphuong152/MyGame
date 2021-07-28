#include "Map.h"
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "tinyxml.h"


using namespace std;

#define TILE_WIDTH 48


CMap::CMap(int id, const char* mapFilePath, int texId, int tilePerRow, int tilePerColumn)
{
	this->id = id;
	this->mapFilePath = mapFilePath;
	this->texId = texId;
	this->tilePerRow = tilePerRow;
	this->tilePerColumn = tilePerColumn;

	layerForeground = NULL;
	layers.clear();
}

void CMap::CreateTileSet()
{
	//cut tileset
	int tileId = 1;
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);

	for (int i = 0; i < tilePerColumn; i++)
	{
		for (int j = 0; j < tilePerRow; j++)
		{

			int t = i * TILE_WIDTH;
			int l = j * TILE_WIDTH;
			int r = l + TILE_WIDTH;
			int b = t + TILE_WIDTH;

			CSprites::GetInstance()->Add(tileId, l, t, r, b, tex);
			//DebugOut(L"[INFO] map added: %d, %d, %d, %d, %d \n", tileId, l, t, r, b);
			tileId++;
		}
	}
}


void CMap::HandleMap()
{
	TiXmlDocument doc(mapFilePath);
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERR] TMX FAILED %s\n", ToLPCWSTR(doc.ErrorDesc()));
		return;
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* layer = nullptr;

	for (layer = root->FirstChildElement(); layer != NULL; layer = layer->NextSiblingElement())
	{
		string name = layer->FirstChildElement()->Value();
		//render map
		//layer k có attribute visible mới add vô vẽ
		// tach layer foreground ra vẽ sau cùng
		if (layer->Attribute("name") != NULL)
		{
			float width, height;
			layer->QueryFloatAttribute("width", &width);
			layer->QueryFloatAttribute("height",&height);

			if (strcmp(layer->Attribute("name"), "Foreground") == 0  )
				layerForeground = new CMapLayer(layer->FirstChildElement(), width,height);
			else {
				const char* attributeVisible = layer->Attribute("visible");
				if (attributeVisible == NULL && name == "data")
				{
					CMapLayer* mLayer = new CMapLayer(layer->FirstChildElement(), width, height);
					layers.push_back(mLayer);
				}
			}
		}
	}
}

void CMap::RenderMap()
{
	for (size_t i = 0; i < layers.size(); i++)
	{
		layers[i]->RenderLayer();
	}
	//DebugOut(L"vo render map \n");
}

void CMap::RenderForeground()
{
	layerForeground->RenderLayer();
}