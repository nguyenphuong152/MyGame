#pragma once

#include "GameObject.h"
#include "Mario.h"

#define KOOPAS_WALKING_SPEED 0.03f;

#define KOOPAS_BBOX_WIDTH 16
#define KOOPAS_BBOX_HEIGHT 20
#define KOOPAS_BBOX_HEIGHT_DIE 16

#define KOOPAS_STATE_WALKING 100
#define KOOPAS_STATE_DIE 200
#define KOOPAS_STATE_DIE_WITH_VELOCITY 300
#define KOOPAS_STATE_RECOVER 400

#define KOOPAS_ANI						70
#define KOOPAS_ANI_WALKING				0
#define KOOPAS_ANI_DIE					1
#define KOOPAS_ANI_DIE_WITH_VELOCITY	2
#define KOOPAS_ANI_RECOVER				s3

class CKoopas : public CGameObject
{
	float start_point;
	float end_point;
	CMario* player;
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	virtual void Render();
public:
	bool isHolded = false;

	CKoopas(float x, float y);
	virtual void SetState(int state);
	void SetAnimation();
};

