#include "MapLayer.h"
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
    int idd = 0;
    for (int i = 0; i <MAPHEIGHT; i++)
    {
        for (int j = 0; j < MAPWIDTH; j++)
        {
            if (idd == tileIdSet.size()) return;

            if (tileIdSet[idd] ==0) {
                idd++;
                continue;
            }
            else {
                CSprites::GetInstance()->Get(tileIdSet[idd])->Draw(0, j * TILE_WIDTH, i * TILE_WIDTH);
                idd++;
            }
           
        }
    }
}

