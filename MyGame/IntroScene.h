#pragma once
#include "Mario.h"
#include "Map.h"
#include "Camera.h"
#include "Curtain.h"
#include "Arrow.h"

#define TREE_LEFT 20008
#define TREE_RIGHT 20009
#define CLOUD_BIG  20010
#define CLOUD_SMALL 20011
#define PLAYER_GAME 20012

class IntroScene {

	CCamera* cam;
	CMap* map;
	CMario* first_mario;
	CMario* second_mario;
	CCurtain* curtain;
	CCurtain* curtain_super_bros;
	CCurtain* curtain_three;
	CArrow* arrow;

	static IntroScene* __instance;

	bool isWalk;
	bool isJump;
	ULONGLONG  walking_start;

	void StartWalking() { isWalk = true; walking_start = GetTickCount64(); };
	void ResetWalking() { isWalk = false; walking_start = 0; }
public:
	static IntroScene* GetInstance();
	void Init(vector<LPGAMEOBJECT> &objects, CMap* map);
	void InitMario();
	void UpdateMarios(DWORD dt);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	CArrow* GetArrow() { return arrow; };

	CMario* GetSecondMario() { return second_mario; };

	void Clear();
};