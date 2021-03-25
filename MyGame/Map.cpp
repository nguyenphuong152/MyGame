#include "Map.h"
#include "Utils.h"
#include "Sprites.h"
#include "Textures.h"
#include "Game.h"
#include "tinyxml.h"
#include "Ground.h"
#include "GameObject.h"
#include "Brick.h"

using namespace std;

#define TILE_WIDTH 48

CMap* CMap::__instance = NULL;

CMap* CMap::GetInstance()
{
	if (__instance == NULL) __instance = new CMap();
	return __instance;
}

void CMap::AddMap(int id, const char* mapFilePath, int texId, int tilePerRow, int tilePerColumn)
{
	this->id = id;
	this->mapFilePath = mapFilePath;
	this->texId = texId;
	this->tilePerRow = tilePerRow;
	this->tilePerColumn = tilePerColumn;
}

void CMap::CreateTileSet()
{
	//cut tileset
	int tileId = 1;
	LPDIRECT3DTEXTURE9 tex = CTextures::GetInstance()->Get(texId);

	for (int i = 0;i < tilePerColumn;i++)
	{		
		for (int j = 0;j < tilePerRow;j++)
		{
			
			int t = i * TILE_WIDTH;
			int l = j * TILE_WIDTH;
			int r = l + TILE_WIDTH;
			int b = t + TILE_WIDTH;

			CSprites::GetInstance()->Add(tileId, l, t, r, b, tex);
			//DebugOut(L"[INFO] map added: %d, %d, %d, %d, %d \n", idd, l, t, r, b);
			tileId++;
		}
	}
}


void CMap::HandleMap()
{	
	TiXmlDocument doc(mapFilePath);
	if (!doc.LoadFile())
	{
		DebugOut(L"[ERR] TMX FAILED %s\n",ToLPCWSTR(doc.ErrorDesc()));
		return ;
	}

	TiXmlElement* root = doc.RootElement();
	TiXmlElement* layer = nullptr;

	for (layer = root->FirstChildElement(); layer != NULL; layer = layer->NextSiblingElement())
	{
		string name = layer->FirstChildElement()->Value();

		//render map
		//layer k có attribute visible mới add vô vẽ
		const char* attributeVisible = layer->Attribute("visible");
		if (attributeVisible == NULL && name == "data")
		{
			CMapLayer* mLayer = new CMapLayer(layer->FirstChildElement());
			layers.push_back(mLayer);
		}
	}
}

void CMap::HandleObjectInMap(vector<LPGAMEOBJECT>& objects)
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
		//render object
		const char* attributeName = layer->Attribute("name");
		TiXmlElement* element = layer->FirstChildElement();
		if (attributeName != NULL)
		{
			CGameObject* obj = NULL;
			float x, y, width, height;
			if (strcmp(attributeName, "Solid") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CGround(x, y, width, height);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "Ghost") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);
					element->QueryFloatAttribute("width", &width);
					element->QueryFloatAttribute("height", &height);

					obj = new CGround(x, y, width, height);
					objects.push_back(obj);

					element = element->NextSiblingElement();
				}
			}
			else if (strcmp(attributeName, "QuestionBlocks") == 0)
			{
				while (element)
				{
					element->QueryFloatAttribute("x", &x);
					element->QueryFloatAttribute("y", &y);

					obj = new CBrick();
					obj->SetPosition(x, y);
					objects.push_back(obj);

					element = element->NextSiblingElement();
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
}