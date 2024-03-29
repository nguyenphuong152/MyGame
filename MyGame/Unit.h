#pragma once
#include "GameObject.h"

class Unit;
typedef Unit* LPUNIT;

class Unit
{
   friend class Grid;
   
private:
    Grid* grid;
    Unit* prev;
    Unit* next;
    float x, y;

    LPGAMEOBJECT obj;

public:
    Unit(Grid* grid, LPGAMEOBJECT obj);
    LPGAMEOBJECT GetObject() { return obj; };
    void Move(float x, float y, float old_x, float old_y);
};