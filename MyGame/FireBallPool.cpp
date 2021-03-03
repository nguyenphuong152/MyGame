#include "FireBallPool.h"
#include "Utils.h"

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

CFireballTest* CFireBallPool::Create()
{
	CFireballTest* newBall;
	// Make sure the pool isn't full.
	if (_firstAvailable != NULL) {
		// Remove it from the available list.
		newBall  = _firstAvailable;
		_firstAvailable = newBall->GetNext();
		return newBall;
	}
	return NULL;
}

void CFireBallPool::Update()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		if (fireballs[i].Animate())
		{
			// Add this particle to the front of the list.
			fireballs[i].SetNext(_firstAvailable);
			_firstAvailable = &fireballs[i];
		};
	}
}