﻿#include "MapLayer.h"
#include "Utils.h"
#include "Sprites.h"

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
    for (int i = 0; i <MAPWORLD_HEIGHT; i++)
    {
        for (int j = 0; j < MAPWORLD_WIDTH; j++)
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

