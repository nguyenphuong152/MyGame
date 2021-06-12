#pragma once

class CMarioState;

#include "GameObject.h"
#include "Input.h"
#include "MarioTail.h"

#define MARIO_WALKING_SPEED			0.25f 
#define MARIO_RUNNING_SPEED			0.4f
#define MARIO_PRE_FLYING_SPEED		0.5f
#define MARIO_START_FLYING_SPEED	0.6f
#define MARIO_FLYING_SPEED			0.3f
//0.1f
#define MARIO_JUMP_SPEED_Y			0.5f
#define MARIO_JUMP_DEFLECT_SPEED	0.4f
#define MARIO_GRAVITY				0.0015f
#define MARIO_SPEED_Y_WHEN_FLOATING	0.005f
#define MARIO_AVERAGE_VY_ON_GROUND	0.08f
#define MARIO_ACCELERATION			0.0004f//giam lai con 0.0001f
#define MARIO_DIE_DEFLECT_SPEED		0.7f

#define MARIO_STATE_DIE			300

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

#define MARIO_ANI_ITEM_SMALL_TO_BIG			33
#define MARIO_ANI_ITEM_BIG_TO_RACOON		34

#define MARIO_ANI_SMALL_HANDLESHELL_IDLE			35
#define MARIO_ANI_SMALL_HANDLESHELL_RUN				36
#define MARIO_ANI_SMALL_HANDLESHELL_JUMP_DROP		37
#define MARIO_ANI_BIG_HANDLESHELL_IDLE				38
#define MARIO_ANI_BIG_HANDLESHELL_RUN				39
#define MARIO_ANI_BIG_HANDLESHELL_JUMP_DROP			40
#define MARIO_ANI_RACCOON_HANDLESHELL_IDLE			41
#define MARIO_ANI_RACCOON_HANDLESHELL_RUN			42
#define MARIO_ANI_RACCOON_HANDLESHELL_JUMP_FLY_DROP 43

#define MARIO_ANI_FIRE_IDLE			44
#define MARIO_ANI_FIRE_WALK			45
#define MARIO_ANI_FIRE_SIT			46
#define MARIO_ANI_FIRE_JUMP			47
#define MARIO_ANI_FIRE_RUN			48
#define MARIO_ANI_FIRE_PRE_FLY		49
#define MARIO_ANI_FIRE_FLY			50
#define MARIO_ANI_FIRE_STOP			51
#define MARIO_ANI_FIRE_KICK			52
#define MARIO_ANI_FIRE_DROP			53
#define MARIO_ANI_FIRE_HANDLESHELL_IDLE				54
#define MARIO_ANI_FIRE_HANDLESHELL_RUN				55
#define MARIO_ANI_FIRE_HANDLESHELL_JUMP_DROP		56
#define MARIO_ANI_FIRE_SHOOT_FIREBALL_IDLE			57
#define MARIO_ANI_FIRE_SHOOT_FIREBALL_JUMP			58

#define MARIO_ANI_RACCOON_ATTACK_BY_TAIL			59
#define MARIO_ANI_IMMORTAL_JUMP						60
#define MARIO_ANI_GET_INTO_PIPE						61
#define MARIO_ANI_DROP_FROP_PIPE					62

#define	MARIO_LEVEL_SMALL		1
#define	MARIO_LEVEL_BIG			2
#define	MARIO_LEVEL_RACOON		3
#define	MARIO_LEVEL_FIRE		4
#define MARIO_LEVEL_IMMORTAL	5


#define MARIO_BIG_BBOX_WIDTH  42
#define MARIO_BIG_BBOX_HEIGHT 77

#define MARIO_BIG_BBOX_SIT_HEIGHT 55

#define MARIO_RACOON_BBOX_WIDTH  63
#define MARIO_RACOON_BBOX_HEIGHT 84

#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 46

#define MARIO_UNTOUCHABLE_TIME 5000

#define DIRECTION_LEFT_TO_RIGHT 1
#define DIRECTION_RIGHT_TO_LEFT -1

#define MARIO_POWER_LEVEL 720
#define MARIO_DEFAULT_LIVE 4

class CMario : public CGameObject
{

	int untouchable;
	DWORD untouchable_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

	int live;
	int level;
public:
	static CMario* __instance;
	CMarioState* marioState;
	CMarioTail* tail;

	int animation;
	int powerLevel;
	bool isOnGround = false;
	bool isSitting = false;
	bool canJumpHigh = false;
	bool canHoldShell = false;
	bool powerMode = false;
	bool isFloating = false;
	bool isJumpOnSwitch = false;
	bool canGoIntoPipe = false;

	//can nhac lai
	bool isKicking = false;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void SetState(int state);

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

	CMarioState* GetState()
	{
		return marioState;
	}

	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; };

	void SetLive(int lives) { live = lives; };
	int GetLive() { return live; };

	void LevelUp();
	void RecalculatePower();
	void SetAnimation(int ani) { animation = ani; }
	int GetCurrentAnimation() { return animation; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void BigMario();
	void RaccoonMario();
	void FireMario();
	void ImmortalMario();
	void Die();

	void LevelMarioDown(CGameObject* object,int enemy_condition);
	void HandleInput(Input input);

	void AttachTail(CMarioTail* tail);

	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderRaccoonMarioBoundingBox();

	static  CMario* GetInstance();
};


