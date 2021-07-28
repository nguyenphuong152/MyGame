#include "Grid.h"
#include "Camera.h"
#include "Game.h"
#include "Ground.h"
#include "Utils.h"
#include "Switch.h"
#include "Koopas.h"
#include "Pipe.h"
#include "BrownParaGoomBa.h"
#include "tinyxml.h"
#include "FireBallPool.h"
#include "BoomerangPool.h"
#include "MiniGoombaPool.h"
#include "HUD.h"

void Grid::UpdatePool(vector<LPGAMEOBJECT>* cobjects, DWORD dt)
{
    CFireBallPool::GetInstance()->Update(dt, cobjects);
    CEffectPool::GetInstance()->Update(dt, cobjects);
    CBoomerangPool::GetInstance()->Update(dt, cobjects);
    CMiniGoombaPool::GetInstance()->Update(dt, cobjects);
}

Grid::Grid()
{
    //clear mang vector
    for (int i = 0; i < NUM_CELL; i++)
    {
        for (int j = 0; j < NUM_CELL; j++)
        {
            cells[i][j] = new Cell();
        }
    }
}

void Grid::Add(LPGAMEOBJECT object,int id)
{
   
   int cellx, celly, xEnd, yEnd;
   
   if (grid_objs.find(id) == grid_objs.end())
   {
       cellx = celly = yEnd = xEnd = 0;
   }
   else
   {
       D3DXVECTOR4 obj_info = grid_objs[id];

       cellx = (int)obj_info[0];
       celly = (int)obj_info[1];
       xEnd = (int)obj_info[2];
       yEnd = (int)obj_info[3];
   }

    for (int i = cellx; i < xEnd+1; i++)
    {
        for (int j = celly; j<yEnd+1; j++)
        {
            cells[i][j]->AddObjectToCell(object);
        }
    }
}

void Grid::ReadFile(const char* mapFilePath)
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
        TiXmlElement* element = layer->FirstChildElement();
    
        int id;
        const char* cellx;
        const char* celly;
        const char* xEnd;
        const char* yEnd;
      
        while (element)
        {
            TiXmlElement* ele = element->FirstChildElement();
            while (ele)
            {
                ele->QueryIntAttribute("id", &id);
                cellx = ele->Attribute("cellx");
                celly = ele->Attribute("celly");

                if (strcmp(ele->Attribute("xEnd"), "NaN") == 0 && strcmp(ele->Attribute("yEnd"), "NaN") == 0)
                {
                    xEnd = cellx;
                    yEnd = celly;
                }
                else {
                    xEnd = ele->Attribute("xEnd");
                    yEnd = ele->Attribute("yEnd");
                }

                D3DXVECTOR4 obj_info = D3DXVECTOR4((float)atoi(cellx), (float)atoi(celly), (float)atoi(xEnd), (float)atoi(yEnd));

                grid_objs[id] = obj_info;

                ele = ele->NextSiblingElement();
            }

            element = element->NextSiblingElement();
        }
    }
}

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT>* coobjs)
{
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

    GetUnitsFromCameraRegion(coobjs);

    for (int i = cell_startX; i < cell_endX+1; i++)
    {
        for (int j = cell_startY; j < cell_endY+1; j++)
        {
            cells[i][j]->Update(dt, coobjs);
        }
    }

    UpdatePool(coobjs, dt);

    CGame::GetInstance()->GetMainCamera()->Update(dt, coobjs);

    if(CGame::GetInstance()->current_scene!=INTRO)HUD::GetInstance()->Update();
}

void Grid::Render()
{
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

    for (int i = cell_startX; i < cell_endX+1; i++)
    {
        for (int j = cell_startY; j < cell_endY+1; j++)
        {
              cells[i][j]->Render();
        }
    }
}




void Grid::GetActiveRegion(int& cell_startX, int& cell_startY, int& cell_endX, int& cell_endY)
{
    CCamera* cam = CGame::GetInstance()->GetMainCamera();
    float cx, cy;
    cam->GetPosition(cx, cy);

    cell_startX = (int)(cx / CELL_SIZE);
    cell_startY = (int)(cy / CELL_SIZE);
    cell_endX = (int)((cx + CAM_WIDTH) / CELL_SIZE);
    cell_endY = (int)((cy + CAM_HEIGHT) / CELL_SIZE);

    if (cell_startX < 0) cell_startX = 0;
    if (cell_startY < 0) cell_startY = 0;
}

void Grid::GetUnitsFromCameraRegion(vector<LPGAMEOBJECT>* units)
{
    
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

  

    for (int i = cell_startX; i < cell_endX+2; i++)
    {
        for (int j = cell_startY; j < cell_endY+2; j++)
        {
            vector<LPGAMEOBJECT> validObjs;
            validObjs = cells[i][j]->GetListObjectInCell();
            units->insert(units->end(), validObjs.begin(), validObjs.end());
        }
    }
}

void Grid::Move(LPGAMEOBJECT object)
{
    float old_x, old_y, x, y;

    object->GetOldPosition(old_x, old_y);
    object->GetPosition(x, y);
    //kiem tra old cell cua unit

    int oldCellX = (int)(old_x / CELL_SIZE);
    int oldCellY = (int)(old_y / CELL_SIZE);

    // cell moi cua unit
    int cellX = (int)(x / CELL_SIZE);
    int cellY = (int)(y / CELL_SIZE);

    // neu k thay doi thi out || ngoai vung thi out
    if (oldCellX == cellX && oldCellY == cellY ) return;

    cells[oldCellX][oldCellY]->RemoveObjectInCell(object);
    cells[cellX][cellY]->AddObjectToCell(object);
}

void Grid::Unload()
{
    for (int i = 0; i < NUM_CELL; i++)
    {
        for (int j = 0; j < NUM_CELL; j++)
        {
            //cells[i][j]->DeleteObject();
            cells[i][j] = NULL;
        }
    }
}

Grid::~Grid()
{
    for (int x = 0; x < NUM_CELL; x++)
    {
        for (int y = 0; y < NUM_CELL; y++)
        {
            delete cells[x][y];
        }
    }
}
