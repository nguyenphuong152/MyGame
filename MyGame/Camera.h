#pragma once
#include "GameObject.h"
#include "Mario.h"



class CCamera :public CGameObject
{
	static CCamera* __instance;
	CMario* player;
	float width;
	float height;
	float cam_center_X;
	float cam_center_Y;
	bool isOnGround;

public:
	bool isReachBoundaryLeft = false;
	bool isReachBoundaryRight = false;
	bool isReachBoundaryTop = false;
	bool isReachBoundaryBottom = false;

	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	static CCamera* GetInstance();

	void FollowPlayerHorizontally();
	void FollowPlayerVertically();
	void SetProperty(float l, float r, float width, float height);
	void InactiveCamera();
	void ResetCamera();
};