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
    //xac dinh unit thuoc o nao cua grid
    int col = (int)(object->x/ CELL_SIZE);
    int row = (int)(object->y/ CELL_SIZE);

    //DebugOut(L"cell %d-%d \n", row, col);

    //them no vao dau cai o ma no thuoc ve
    object->prev = NULL;
    object->next = cells[row][col];
   
    cells[row][col] = object;

    if (object->next != NULL)
    {
        object->next->prev = object;
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
        const char* attributeName = layer->Attribute("name");
        TiXmlElement* element = layer->FirstChildElement();

        int id, cellx, celly, xEnd, yEnd;
        if (attributeName != NULL)
        {
            if (strcmp(attributeName, "WoodBlock") == 0)
            {
                TiXmlElement* ele = element->FirstChild("group")->ToElement();
                while (ele)
                {
                    ele->QueryIntAttribute("id", &id);
                    ele->QueryIntAttribute("cellx", &cellx);
                    ele->QueryIntAttribute("celly", &celly);
                    ele->QueryIntAttribute("xEnd", &xEnd);
                    ele->QueryIntAttribute("yEnd", &yEnd);

                    D3DXVECTOR4 obj_info = D3DXVECTOR4(cellx, celly, xEnd, yEnd);

                    grid_objs[id] = obj_info;

                    ele = ele->NextSiblingElement();
                }
                //DebugOut(L"[DONE LOADING SOLID] - %d \n", objects.size());
            }
        }
    }
}

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT>* coobjs)
{
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

    for (int i = cell_startY; i < cell_endY+1; i++)
    {
        for (int j = cell_startX; j < cell_endX+1; j++)
        {
            if (cells[i][j] != NULL)
            {
                cells[i][j]->Update(dt, coobjs);
            }
        }
    }
}

void Grid::Render()
{
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

    for (int i = cell_startY; i < cell_endY+1; i++)
    {
        for (int j = cell_startX; j < cell_endX+1; j++)
        {
            if (cells[i][j] != NULL)
            {
                cells[i][j]->Render();
            }
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

    //DebugOut(L"cell k null %d -- %d---%d---%d \n", cell_startX, cell_startY,cell_endX,cell_endY);

    for (int i = cell_startY; i < cell_endY+1; i++)
    {
        for (int j = cell_startX; j < cell_endX+1; j++)
        {
            if (cells[i][j] != NULL)
            {
                vector<LPGAMEOBJECT> validObjs;
                validObjs.clear();
                validObjs = cells[i][j]->GetListObjectInCell();

                units->insert(units->end(), validObjs.begin(),validObjs.end());
            }
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

    // thao ra khoi list unit thuoc old cell 
    if (object->prev != NULL)
    {
        object->prev->next = object->next;
    }

    if (object->next != NULL)
    {
        object->next->prev = object->prev;
    }

    // neu no o dau list cua  oldcell thi go ra, va thay doi dau list cua old cell
    if (cells[oldCellY][oldCellX] == object)
    {
        cells[oldCellY][oldCellX] = object->next;
    }
    // add lai vao grid , o list cua cell moi

    Add(object);
}

void Grid::Unload()
{
    for (int i = 0; i < NUM_CELL; i++)
    {
        for (int j = 0; j < NUM_CELL; j++)
        {
            cells[i][j] = NULL;
        }
    }
}
