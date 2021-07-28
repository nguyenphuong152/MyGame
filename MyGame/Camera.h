#pragma once
#include "GameObject.h"
#include "Mario.h"
#include "HiddenScene.h"

#define CAMERA_AUTO_VELOCITY_X 0.1f;

#define CAM_WIDTH	760
#define CAM_HEIGHT	600

#define CAMERA_STATE_NORMAL			1
#define CAMERA_STATE_HIDDEN_SCENE1	2
#define CAMERA_STATE_HIDDEN_SCENE3	3

#define CAM_START_X 20

#define HIDDEN_SCENE_1_CAM_X 6700
#define HIDDEN_SCENE_1_CAM_Y 750

#define SECRET_PIPE_X_1	6500
#define SECRET_PIPE_Y_1 100

class CCamera :public CGameObject
{
	static CCamera* __instance;
	CMario* player;

	float width;
	float height;
	float cam_center_X;
	float cam_center_Y;

	float start_y;

	bool isReachBoundaryBottom;
	CHiddenScene* hiddenscenes;
public:
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void SetState(int state);

	void FollowPlayerHorizontally();
	void FollowPlayerVertically();

	CHiddenScene* GetHiddenScene() { return hiddenscenes; };
	void GetCamPos(float& x, float& y, float& cam_width, float& cam_height);
	
	CCamera(float y,float width, float height);
	void InactiveCamera();
	void InitCamera();
	void AdjustPositionToHiddenScene();
	void GoBackToNormal();
	void AddHiddenScene(CHiddenScene* h) { this->hiddenscenes = h; };
	void AutoMoveToSecretScreen();
};