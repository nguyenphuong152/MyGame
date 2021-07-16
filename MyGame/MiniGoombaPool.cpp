#include "MiniGoombaPool.h"
#include "Utils.h"

CMiniGoombaPool* CMiniGoombaPool::__instance = NULL;

CMiniGoombaPool::CMiniGoombaPool()
{
	//The first one is available.
	minigoombas[0] = new CMiniGoomba();
	_firstAvailable = minigoombas[0];

	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		minigoombas[i + 1] = new CMiniGoomba();
		minigoombas[i]->SetNext(minigoombas[i + 1]);
	}

	// The last one terminates the list.
	minigoombas[POOL_SIZE - 1]->SetNext(NULL);
}

CMiniGoomba* CMiniGoombaPool::Create()
{
	// Make sure the pool isn't full --- all fireballs are used.
	if (_firstAvailable != NULL) {
		CMiniGoomba* g = _firstAvailable;
		g->SetAnimation(ani_set);
		_firstAvailable = g->GetNext();
		return g;
	}
	else {
		return NULL;
		DebugOut(L"null \n");
	}
}


void CMiniGoombaPool::Update(DWORD dt, vector<LPGAMEOBJECT>* coObject)
{
	//if (_firstAvailable == NULL) return;

	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (minigoombas[i]->_state.live.inUse == true)
		{
			minigoombas[i]->Update(dt, coObject);
		}

		if (minigoombas[i]->FinishShooting())
		{
			// Add this particle to the front of the list.
			minigoombas[i]->SetNext(_firstAvailable);
			_firstAvailable = minigoombas[i];
		};
	}
}

void CMiniGoombaPool::Render()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (minigoombas[i]->_state.live.inUse == true)
		{
			minigoombas[i]->Render();
		}
	}
}

void CMiniGoombaPool::Unload()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		minigoombas[i] = NULL;
	}
	_firstAvailable = NULL;
	__instance = NULL;
}

CMiniGoombaPool* CMiniGoombaPool::GetInstance()
{
	if (__instance == NULL) __instance = new CMiniGoombaPool();
	return __instance;
}


void CMiniGoombaPool::Init(vector<LPGAMEOBJECT>& objects, int ani)
{
	SetMiniGoombaAnimation(ani);
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects.push_back(minigoombas[i]);
	}
}