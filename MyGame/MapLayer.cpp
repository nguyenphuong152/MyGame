#include "MapLayer.h"
#include "Utils.h"
#include "Sprites.h"


CMapLayer::CMapLayer(TiXmlElement* layer) {
	mapInfo = layer->GetText();
}

void CMapLayer::RenderLayer()
{
    vector<string> numbs = split(mapInfo, ",");

    int idd = -1;
    int tileId = 0;
    for (int i = 0; i < TILEPERCOLUMN; i++)
    {
        idd++;
        for (int j = 0; j < TILEPERROW; j++)
        {
            if (idd == 7216) return;
            tileId = atoi(numbs.at(idd).c_str());
            if (tileId==0) {
                idd++;
                continue;
            }
            CSprites::GetInstance()->Get(3)->Draw(0, j * 48, i * 48);
            DebugOut(L"[render map] \n");
            idd++;
        }
    }
}

