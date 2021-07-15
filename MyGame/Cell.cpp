#include "Cell.h"



void Cell::AddObjectToCell(LPGAMEOBJECT obj)
{
	if (objects.find(obj) == objects.end())
	{
		objects.insert(obj);
	}
}

void Cell::RemoveObjectInCell(LPGAMEOBJECT obj)
{
	if (objects.find(obj) != objects.end())
	{
		objects.erase(obj);
	}
}

vector<LPGAMEOBJECT> Cell::GetListObjectInCell()
{
	vector<LPGAMEOBJECT> objs;
	for (auto o : objects)
	{
		if (o->isEnable == true)
			objs.push_back(o);
	}
}

void Cell::Update(DWORD dt, vector<LPGAMEOBJECT>* coObj)
{
	vector<LPGAMEOBJECT> validObjs = GetListObjectInCell();
	for (size_t i = 0; i < validObjs.size(); i++)
	{
		validObjs[i]->Update(dt, coObj);
	}
}

void Cell::Render()
{
}
