#pragma once
#include "MarioOnGroundStates.h"

class CMarioStateIdle : public CMarioOnGroundStates 
{
public:
	static CMarioStateIdle* __instance;

	CMarioStateIdle();
	virtual ~CMarioStateIdle() {};

	virtual void HandleInput(CMario& mario) ;
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt,CMario& mario);
	static CMarioStateIdle* GetInstance();

};
