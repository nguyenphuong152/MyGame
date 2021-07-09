#include "Grid.h"
#include "Camera.h"
#include "Game.h"
#include "Ground.h"
#include "Utils.h"

Grid::Grid()
{
    //clear mang vector
    for (int i = 0; i < NUM_CELL; i++)
    {
        for (int j = 0; j < NUM_CELL; j++)
        {
            cells[i][j] = NULL ;
        }
    }
}

void Grid::Add(LPGAMEOBJECT object)
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

void Grid::Update(DWORD dt, vector<LPGAMEOBJECT>* coobjs)
{
    int cell_startX, cell_startY, cell_endX, cell_endY;
    GetActiveRegion(cell_startX, cell_startY, cell_endX, cell_endY);

    for (int i = cell_startY; i < cell_endY+1; i++)
    {
        for (int j = cell_startX; j < cell_endX+1; j++)
        {
            LPGAMEOBJECT obj = cells[i][j];
            while (obj != NULL)
            {
                if (obj->isEnable)
                {
                    obj->Update(dt, coobjs);
                }
                obj = obj->next;
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
            LPGAMEOBJECT obj = cells[i][j];
            while (obj != NULL)
            {
                if (obj->isEnable)
                {
                    obj->Render();
                }
                obj = obj->next;
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
            LPGAMEOBJECT objs = cells[i][j];
            while (objs != NULL)
            {
                if (objs->isEnable)
                {
                    units->push_back(objs);
                }
                objs = objs->next;    
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