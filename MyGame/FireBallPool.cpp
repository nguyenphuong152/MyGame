#include "FireBallPool.h"
#include "Utils.h"

CFireBallPool* CFireBallPool::__instance = NULL;

CFireBallPool::CFireBallPool()
{
	//The first one is available.
	_firstAvailable = &fireballs[0];
	
	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		fireballs[i].SetNext(&fireballs[i + 1]);
	}

	// The last one terminates the list.
	fireballs[POOL_SIZE - 1].SetNext(NULL);
}

void CFireBallPool::Create(float x, float y,bool isShootingUp,CMario* mario)
{ 
	// Make sure the pool isn't full.
	if (_firstAvailable != NULL) {
		CFireball* newBall = _firstAvailable;
		_firstAvailable = newBall->GetNext();
		newBall->Init(x, y,isShootingUp,mario);
		for (int i = 0; i < POOL_SIZE; i++)
		{
			if (newBall == &fireballs[i])
			{
				DebugOut(L"have ball %d %d \n", i, fireballs[i].isEnable);
			}
		}
	}
	else {
		DebugOut(L"null \n");
	}
}


void CFireBallPool::Update()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		//DebugOut(L"have ball %d %d \n", i, fireballs[i].isEnable);
		//if (fireballs[i].isEnable)
		//{
		//	// Add this particle to the front of the list.
		//	fireballs[i].SetNext(_firstAvailable);
		//	_firstAvailable = &fireballs[i];
		//};
	}
}

CFireBallPool* CFireBallPool::GetInstance()
{
	if (__instance == NULL) __instance = new CFireBallPool();
	return __instance;
}