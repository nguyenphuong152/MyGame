﻿#include "MapLayer.h"
#include "Utils.h"
#include "Sprites.h"
#include "Game.h"

#define TILE_WIDTH 48

CMapLayer::CMapLayer(TiXmlElement* layer, float width, float height) {
    mapInfo = layer->GetText();

    this->height = height;
    this->width = width;
    //chuyển string vector thành int để vẽ
    vector<string> tileIdSetRaw = split(mapInfo, ",");

    int id =0;
    
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
           if (id > tileIdSetRaw.size()) return;
           tileset[i][j] = atoi(tileIdSetRaw[id].c_str());
            //DebugOut(L"helo %d --- %d ---- %d \n", i, j, atoi(tileIdSetRaw[id].c_str()));
           id++;
        }
    }
}

void CMapLayer::SetRenderRegion(int& cell_startX, int& cell_startY, int& cell_endX, int& cell_endY)
{
    float camX, camY;
    CGame::GetInstance()->GetMainCamera()->GetPosition(camX, camY);

    cell_startX = camX / TILE_WIDTH;
    cell_startY = camY / TILE_WIDTH;
    cell_endX = (camX + CAM_WIDTH) / TILE_WIDTH + 1;
    cell_endY = (camY + CAM_HEIGHT) / TILE_WIDTH + 1;
}


void CMapLayer::RenderLayer()
{
  
   int cell_startX, cell_startY, cell_endX, cell_endY;

   SetRenderRegion(cell_startX, cell_startY, cell_endX, cell_endY);

   for (int i = cell_startY; i < cell_endY; i++)
    {
        for (int j = cell_startX; j < cell_endX; j++)
        {
           if (tileset[i][j] != 0) {
               CSprites::GetInstance()->Get(tileset[i][j])->Draw(-1, 1, j * TILE_WIDTH, i * TILE_WIDTH);
            }
        }
    }
}

