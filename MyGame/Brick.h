#pragma once
#include "GameObject.h"

#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_UNTOUCH 10
#define BRICK_STATE_TOUCHED 20

#define BRICK_ANI_UNTOUCH 0
#define BRICK_ANI_TOUCHED 1

#define BRICK_DEFLECT_POS 20
//#define BRICK_TRANSITION_SPEED 3

class CBrick :public CGameObject
{
	float oldY; //lưu lại vị trí để cục gạch nhảy lên một xíu khi mario đụng vô
public:
	CBrick();
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	//&l la ref trong c# do nhe
};

