#include "MapLayer.h"
#include "Utils.h"
#include "Sprites.h"
#include "Game.h"

#define TILE_WIDTH 48

CMapLayer::CMapLayer(TiXmlElement* layer) {
	mapInfo = layer->GetText();

    //chuyển string vector thành int để vẽ
    vector<string> tileIdSetRaw = split(mapInfo, ",");

    for (size_t i = 0; i < tileIdSetRaw.size(); i++)
    {
        tileIdSet.push_back(atoi(tileIdSetRaw[i].c_str()));
    }
}

void CMapLayer::RenderLayer()
{
    int id = 0;
    float width, height;

    if (CGame::GetInstance()->current_scene == 4)
    {
        width = MAPWORLD_WIDTH;
        height = MAPWORLD_HEIGHT;
    }
    else if (CGame::GetInstance()->current_scene == 3)
    {
        width = MAPWIDTH;
        height = MAPHEIGHT;
    }

    for (int i = 0; i <height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (id == tileIdSet.size()) return;

            if (tileIdSet[id] ==0) {
                id++;
                continue;
            }
            else {
                CSprites::GetInstance()->Get(tileIdSet[id])->Draw(-1,1, j * TILE_WIDTH, i * TILE_WIDTH);
                id++;
            }
           
        }
    }
}

