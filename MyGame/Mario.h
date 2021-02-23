#pragma once

class CMarioState;

#include "GameObject.h"
#include "Input.h"

#define MARIO_WALKING_SPEED		0.15f 
#define MARIO_RUNNING_SPEED 0.18f
#define MARIO_PRE_FLYING_SPEED 0.25f
//0.1f
#define MARIO_JUMP_SPEED_Y			0.4f
#define MARIO_JUMP_HIGH_SPEED_Y		0.25f
#define MARIO_JUMP_DEFLECT_SPEED	0.2f
#define MARIO_GRAVITY				0.0015f
#define MARIO_SPEED_Y_WHEN_FLOATING	0.0005f
#define MARIO_AVERAGE_VY_ON_GROUND	0.05f
#define MARIO_ACCELERATION			0.0004f//giam lai con 0.0001f
#define MARIO_DIE_DEFLECT_SPEED		0.5f

#define MARIO_STATE_IDLE			0
#define MARIO_STATE_WALKING       100
#define MARIO_STATE_JUMP			200
#define MARIO_STATE_DIE			300
#define MARIO_STATE_STOP_DOING	400

#define	MARIO_LEVEL_SMALL	1
#define	MARIO_LEVEL_BIG		2
#define MARIO_LEVEL_RACOON	3


//thu tu theo ani add trong file txt
#define MARIO_ANI_SMALL_IDLE		0 
#define MARIO_ANI_SMALL_WALK		1
#define MARIO_ANI_SMALL_JUMP		2
#define MARIO_ANI_SMALL_RUN			3
#define MARIO_ANI_SMALL_PRE_FLY		4
#define MARIO_ANI_SMALL_FLY			5
#define MARIO_ANI_SMALL_STOP		6
#define MARIO_ANI_SMALL_KICK		7
#define MARIO_ANI_SMALL_DROP		8
#define MARIO_ANI_DIE				9 

#define MARIO_ANI_BIG_IDLE			10
#define MARIO_ANI_BIG_WALK			11
#define MARIO_ANI_BIG_SIT			12
#define MARIO_ANI_BIG_JUMP			13
#define MARIO_ANI_BIG_RUN			14
#define MARIO_ANI_BIG_PRE_FLY		15
#define MARIO_ANI_BIG_FLY			16
#define MARIO_ANI_BIG_STOP			17
#define MARIO_ANI_BIG_KICK			18
#define MARIO_ANI_BIG_DROP			19

#define MARIO_ANI_RACCOON_IDLE		20
#define MARIO_ANI_RACCOON_WALK		21
#define MARIO_ANI_RACCOON_SIT		22
#define MARIO_ANI_RACCOON_JUMP		23
#define MARIO_ANI_RACCOON_RUN		24
#define MARIO_ANI_RACCOON_DROP		25
#define MARIO_ANI_RACCOON_PRE_FLY	26
#define MARIO_ANI_RACCOON_FLY		27
#define MARIO_ANI_RACCOON_STOP		28
#define MARIO_ANI_RACCOON_SPIN		29
#define MARIO_ANI_RACCOON_KICK		30
#define MARIO_ANI_RACCOON_DROP		31
#define MARIO_ANI_RACCOON_DROP_FLY	32

#define MARIO_ANI_ITEM_SMALL_TO_BIG	33
#define MARIO_ANI_ITEM_BOOM			34

#define MARIO_ANI_SMALL_HANDLESHELL_IDLE			35
#define MARIO_ANI_SMALL_HANDLESHELL_RUN				36
#define MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP		37
#define MARIO_ANI_BIG_HANDLESHELL_IDLE				38
#define MARIO_ANI_BIG_HANDLESHELL_RUN				39
#define MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP			40
#define MARIO_ANI_RACCOON_HANDLESHELL_IDLE			41
#define MARIO_ANI_RACCOON_HANDLESHELL_RUN			42
#define MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP 43

#define MARIO_BIG_BBOX_WIDTH  15
#define MARIO_BIG_BBOX_HEIGHT 26
#define MARIO_BIG_BBOX_SIT_HEIGHT 17

#define MARIO_RACOON_BBOX_WIDTH  21
#define MARIO_RACOON_BBOX_HEIGHT 27
#define MARIO_RACOON_BBOX_SIT_HEIGHT 17

#define MARIO_SMALL_BBOX_WIDTH  13
#define MARIO_SMALL_BBOX_HEIGHT 15

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_SPINNING_TIME 300

#define DIRECTION_LEFT_TO_RIGHT 1
#define DIRECTION_RIGHT_TO_LEFT -1

//type  handle animation with time


class CMario : public CGameObject
{

	int untouchable;
	DWORD untouchable_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

public:
	CMarioState* marioState;
	int level;
	int animation;
	bool isOnGround = false;
	bool isSitting = false;
	bool canFlyHigh = false;
	bool powerMode = false;
	bool isFloating = false;

	int power;
	DWORD power_start;

	int spinnable;
	DWORD spinning_start;

	DWORD highjump_start;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();

	void InitState();
	void SetVelocityX(float velocity_x) {
		vx = velocity_x;
	}
	void SetVelocityY(float velocity_y) {
		vy = velocity_y;
	}
	void SetDirection(int dir) {
		nx = dir;
	}
	void ChangeState(CMarioState* new_state) {
		marioState = new_state;
	}


	void SetLevel(int l) { level = l; }
	void SetAnimation(int ani) { animation = ani; }
	int GetCurrentAnimation() { return animation; }

	void StartSpinning() { spinnable = 1; spinning_start = GetTickCount(); }
	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount(); }
	void TogglePowerMode() { power_start = GetTickCount(); }
	void StartHighJump() { highjump_start = GetTickCount(); }
	void Reset();
	void TransformRacoon();
	void HandleInput(Input input);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	//Kiem tra collision voi item
	void CheckCollisionWithItems(vector<LPGAMEOBJECT>* listItem);

	//xu li animation co nhieu hon 1 frame hoac xet thoi gian cho mario untouch hay thay doi gi do
	void HandleAnimationWithTime(int define_time, DWORD start_time,int status);
};


