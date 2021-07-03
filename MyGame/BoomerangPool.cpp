#include "BoomerangPool.h"
#include "Utils.h"

CBoomerangPool* CBoomerangPool::__instance = NULL;

CBoomerangPool::CBoomerangPool()
{
	//The first one is available.
	boomerangs[0] = new CBoomerang();
	_firstAvailable = boomerangs[0];

	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		boomerangs[i + 1] = new CBoomerang();
		boomerangs[i]->SetNext(boomerangs[i + 1]);
	}

	// The last one terminates the list.
	boomerangs[POOL_SIZE - 1]->SetNext(NULL);
}

CBoomerang* CBoomerangPool::Create()
{
	// Make sure the pool isn't full --- all fireballs are used.
	if (_firstAvailable != NULL) {
		CBoomerang* newBoomerang = _firstAvailable;
		newBoomerang->SetAnimation(ani_set);
		_firstAvailable = newBoomerang->GetNext();
		return newBoomerang;
	}
	else {
		return NULL;
		DebugOut(L"null \n");
	}
}


void CBoomerangPool::Update()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		//DebugOut(L"die %d, stt  %d \n", fireballs[i].isEnable, i);
		if (boomerangs[i]->FinishShooting())
		{
			// Add this particle to the front of the list.
			boomerangs[i]->SetNext(_firstAvailable);
			_firstAvailable = boomerangs[i];
		};
	}
}

CBoomerangPool* CBoomerangPool::GetInstance()
{
	if (__instance == NULL) __instance = new CBoomerangPool();
	return __instance;
}


void CBoomerangPool::Init(vector<LPGAMEOBJECT>& objects, int ani)
{
	SetBoomerangAnimation(ani);
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects.push_back(boomerangs[i]);
	}
}