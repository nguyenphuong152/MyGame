#include "EffectPool.h"
#include "Utils.h"

CEffectPool* CEffectPool::__instance = NULL;

CEffectPool::CEffectPool()
{
	//The first one is available.	
	effects[0] = new CEffect();
	_firstAvailable = effects[0];

	// Each particle points to the next.
	for (int i = 0; i < POOL_SIZE - 1; i++)
	{
		effects[i + 1] = new CEffect();
		effects[i]->SetNext(effects[i + 1]);
	}

	// The last one terminates the list.
	effects[POOL_SIZE - 1]->SetNext(NULL);
}

CEffect* CEffectPool::Create()
{
	// Make sure the pool isn't full --- all fireballs are used.
	if (_firstAvailable != NULL) {
		CEffect* effect = _firstAvailable;
		effect->SetAnimation(ani_set);
		_firstAvailable = effect->GetNext();
		return effect;
	}
	else {
		return NULL;
		DebugOut(L"null \n");
	}
}


void CEffectPool::Update()
{
	if (_firstAvailable == NULL) return;
	for (int i = 0; i < POOL_SIZE; i++)
	{
		//DebugOut(L"die %d, stt  %d \n", fireballs[i].isEnable, i);
		if (effects[i]->FinishAnimated())
		{
			// Add this particle to the front of the list.
			effects[i]->SetNext(_firstAvailable);
			_firstAvailable = effects[i];
		};
	}
}

CEffectPool* CEffectPool::GetInstance()
{
	if (__instance == NULL) __instance = new CEffectPool();
	return __instance;
}

void CEffectPool::Init(vector<LPGAMEOBJECT> &objects, int ani)
{
	SetEffectAnimation(ani);
	for (int i = 0; i < POOL_SIZE; i++)
	{
		objects.push_back(effects[i]);
	}
}

void CEffectPool::Unload()
{
	for (int i = 0; i < POOL_SIZE; i++)
	{
		effects[i] = NULL;
	}
	_firstAvailable = NULL;
	__instance = NULL;
}
