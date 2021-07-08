#include "Grid.h"
#include "Camera.h"
#include "Game.h"
#include "Ground.h"
#include "Utils.h"

Grid::Grid(int mWidth, int mHeight, int cWidth, int cHeight)
{
    cols = mWidth / cWidth;
    rows = mHeight / cHeight;

    cell_height = cHeight;
    cell_width = cWidth;

    //set size cho vector 2d 
    cells.resize(rows);

    for (int i = 0; i < cells.size(); i++)
        cells[i].resize(cols);

    //clear mang vector
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            cells[i][j] = NULL ;
        }
    }
    DebugOut(L"hellp \n");
}

void Grid::Add(Unit* unit)
{
    //xac dinh unit thuoc o nao cua grid
    int col = (int)(unit->x/ cell_width);
    int row = (int)(unit->y/ cell_height);

    //DebugOut(L"cell %d-%d \n", row, col);

    //them no vao dau cai o ma no thuoc ve
    unit->prev = NULL;
    unit->next = cells[row][col];
   
    cells[row][col] = unit;

    if (unit->next != NULL)
    {
        unit->next->prev = unit;
    }
}

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT>* coobjs)
{
 /*   CCamera* cam = CGame::GetInstance()->GetMainCamera();
    float cx, cy;
    float cell_startX, cell_startY, cell_endX, cell_endY;
    cam->GetPosition(cx, cy);

    cell_startX =  (int)(cx / cell_width);
    cell_startY =  (int)(cy / cell_height);
    cell_endX = (int)((cx + CAM_WIDTH) / cell_width + 1);
    cell_endY = (int)((cy + CAM_HEIGHT) / cell_height + 1);*/

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            if(cells[i][j]!=NULL) 

             HandleCell(cells[i][j],dt,coobjs);
        }
    }
}


void Grid::HandleCell(Unit* unit,DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
    while (unit != NULL)
    {
        if (unit->obj->isEnable == true)
        {
            unit->obj->Update(dt, coObjects);
        }
        unit = unit->next;
    }
}

void Grid::GetUnitsFromCameraRegion(vector<LPUNIT>* units)
{
    CCamera* cam = CGame::GetInstance()->GetMainCamera();
    float cx, cy;
    int cell_startX, cell_startY, cell_endX, cell_endY;
    cam->GetPosition(cx, cy);
  
    cell_startX = (int)(cx / cell_width);
    cell_startY = (int) (cy / cell_height);
    cell_endX = (int)((cx + CAM_WIDTH) / cell_width + 1);
    cell_endY = (int)((cy + CAM_HEIGHT) / cell_height+ 1);

    //DebugOut(L"cell k null %d -- %d---%d---%d \n", cell_startX, cell_startY,cell_endX,cell_endY);

    for (int i = cell_startY; i < cell_endY; i++)
    {
        for (int j = cell_startX; j < cell_endX; j++)
        {
            Unit* unit = cells[i][j];
            if (unit == NULL) continue;

            while (unit != NULL)
            {
                units->push_back(unit);
                unit = unit->next;
            }
        }
    }
}

void Grid::Move(Unit* unit, float x, float y)
{
    //kiem tra old cell cua unit
    int oldCellX = (int)(unit->x / cell_width);
    int oldCellY = (int)(unit->y / cell_height);

    // cell moi cua unit
    int cellX = (int)(x / cell_width);
    int cellY = (int)(y / cell_height);

    unit->x = x;
    unit->y = y;

    // neu k thay doi thi out
    if (oldCellX == cellX && oldCellY == cellY) return;

    // thao ra khoi list unit thuoc old cell 
    if (unit->prev != NULL)
    {
        unit->prev->next = unit->next;
    }

    if (unit->next != NULL)
    {
        unit->next->prev = unit->prev;
    }

    // neu no o dau list cua  oldcell thi go ra, va thay doi dau list cua old cell
    if (cells[oldCellX][oldCellY] == unit)
    {
        cells[oldCellX][oldCellY] = unit->next;
    }
    // add lai vao grid , o list cua cell moi
    Add(unit);
}