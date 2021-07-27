#pragma once
#include "MarioOnGroundStates.h"

#define MARIO_OVERWORLD_BBOX_WIDTH 45


class CMarioOverworldState :public CMarioOnGroundStates
{
	int scene_id;
public:
	static CMarioOverworldState* __instance;

	CMarioOverworldState();
	virtual ~CMarioOverworldState() {};

	virtual void HandleInput(CMario& mario, Input input);
	virtual void Enter(CMario& mario);
	virtual void Update(DWORD dt, CMario& mario);
	static CMarioOverworldState* GetInstance();

	void SetSceneSwitching(int scene);
	void GetBoundingBox(CMario &mario,float& l, float& t, float& r, float& b);
};