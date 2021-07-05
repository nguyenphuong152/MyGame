#include "FireBallPool.h"
#include "Utils.h"

CFireBallPool* CFireBallPool::__instance = NULL;

CFireBallPool::CFireBallPool()
{
	//The first one is available.
	fireballs[0] = new CFireball();
	_firstAvailable = fireballs[0];
	
	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		fireballs[i + 1] = new CFireball();
		fireballs[i]->SetNext(fireballs[i + 1]);
	}

	// The last one terminates the list.
	fireballs[POOL_SIZE - 1]->SetNext(NULL);
}

CFireball* CFireBallPool::Create()
{ 
	// Make sure the pool isn't full --- all fireballs are used.
	if (_firstAvailable != NULL) {
		CFireball* newBall = _firstAvailable;
		newBall->SetAnimation(ani_set);
		_firstAvailable = newBall->GetNext();
		return newBall;
	}
	else {
		return NULL;
		DebugOut(L"null \n");
	}
}


void CFireBallPool::Update()
{
	if (_firstAvailable == NULL) return;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		//DebugOut(L"die %d, stt  %d \n", fireballs[i].isEnable, i);
		if (fireballs[i]->FinishShooting())
		{
			// Add this particle to the front of the list.
			fireballs[i]->SetNext(_firstAvailable);
			_firstAvailable = fireballs[i];
		};
	}
}

void CFireBallPool::Unload()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		fireballs[i] = NULL;
	}
	_firstAvailable = NULL;
	__instance = NULL;
}

CFireBallPool* CFireBallPool::GetInstance()
{
	if (__instance == NULL) __instance = new CFireBallPool();
	return __instance;
}


void CFireBallPool::Init(vector<LPGAMEOBJECT> &objects, int ani)
{
	SetFireballAnimation(ani);
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects.push_back(fireballs[i]);
	}
}