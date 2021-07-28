#pragma once
#include "MarioOnGroundStates.h"

#define MARIO_TRANSFORM_TIME 600

class CMarioStateTransform : public CMarioOnGroundStates
{
private:
	ULONGLONG _transformStart;

public:
	int isTransform;
	static CMarioStateTransform* __instance;
	void StartTransform() { _transformStart = GetTickCount64(); isTransform = 1; };
	CMarioStateTransform();
	virtual ~CMarioStateTransform() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioStateTransform* GetInstance();

};

