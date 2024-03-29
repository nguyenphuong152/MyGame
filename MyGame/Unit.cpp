#include "Unit.h"
#include "Grid.h"

Unit::Unit(Grid* g,LPGAMEOBJECT object)
{
	grid = g;
	obj = object;

	x = object->x;
	y = object->y;
	prev = next = NULL;

	grid->Add(this);
}

void Unit::Move(float x, float y, float old_x, float old_y)
{
	grid->Move(this, x, y,old_x, old_y);
}
