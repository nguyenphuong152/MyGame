#pragma once
#include "MarioOnGroundStates.h"

#define MARIO_TRANSFORM_TIME 1000

class CMarioStateTransform : public CMarioOnGroundStates
{
private:
	ULONGLONG _transformStart;
	int isTransform = 0;

public:
	static CMarioStateTransform* __instance;
	void StartTransform() { _transformStart = GetTickCount64(); isTransform = 1; };
	CMarioStateTransform();
	virtual ~CMarioStateTransform() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateTransform* GetInstance();

};

