#include "FireBallPool.h"
#include "Utils.h"

CFireBallPool::CFireBallPool(CMario *mario)
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

	this->player = mario;
}

void CFireBallPool::Create(float x, float y,bool isShootingUp)
{ 
	// Make sure the pool isn't full.
	if (_firstAvailable != NULL) {
		CFireballTest* newBall = _firstAvailable;
		_firstAvailable = newBall->GetNext();
		newBall->Init(x, y,player,isShootingUp);
		for (int i = 0; i < POOL_SIZE; i++)
		{
			if (newBall == &fireballs[i])
			{
				DebugOut(L"have ball %d \n",i);
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
		if (fireballs[i].isEnable)
		{
			// Add this particle to the front of the list.
			fireballs[i].SetNext(_firstAvailable);
			_firstAvailable = &fireballs[i];
		};
	}
}