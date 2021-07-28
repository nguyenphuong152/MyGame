#pragma once

class CMarioState;

#include "GameObject.h"
#include "Input.h"
#include "MarioTail.h"

#define MARIO_WALKING_SPEED			0.25f 
#define MARIO_RUNNING_SPEED			0.4f
#define MARIO_PRE_FLYING_SPEED		0.5f
#define MARIO_START_FLYING_SPEED	0.8f
#define MARIO_FLYING_SPEED			0.4f
//0.1f
#define MARIO_JUMP_SPEED_Y			0.6f
#define MARIO_GRAVITY				0.002f
#define MARIO_SPEED_Y_WHEN_FLOATING	0.005f
#define MARIO_AVERAGE_VY_ON_GROUND	0.08f
#define MARIO_ACCELERATION			0.0006f//giam lai con 0.0001f
#define MARIO_DIE_DEFLECT_SPEED		0.7f

#define MARIO_STATE_DIE			300
#define MARIO_STATE_ALIVE		400
#define MARIO_WALKING_ON_HIDDEN_SCENE_3	500

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

#define MARIO_ANI_WALK_OW_SMALL						0
#define MARIO_ANI_WALK_OW_BIG						1
#define MARIO_ANI_WALK_OW_RACCOON					2

#define	MARIO_LEVEL_SMALL		1
#define	MARIO_LEVEL_BIG			2
#define	MARIO_LEVEL_RACOON		3
#define	MARIO_LEVEL_FIRE		4
#define MARIO_LEVEL_IMMORTAL	5


#define MARIO_BIG_BBOX_WIDTH  44
#define MARIO_BIG_BBOX_HEIGHT 82

#define MARIO_BIG_BBOX_SIT_HEIGHT 55

#define MARIO_RACOON_BBOX_WIDTH  62
#define MARIO_RACOON_BBOX_HEIGHT 82

#define MARIO_SMALL_BBOX_WIDTH  40
#define MARIO_SMALL_BBOX_HEIGHT 48

#define MARIO_UNTOUCHABLE_TIME 5000
#define MARIO_DIE_TIME		   100

#define DIRECTION_LEFT_TO_RIGHT 1
#define DIRECTION_RIGHT_TO_LEFT -1

#define MARIO_POWER_LEVEL 720
#define MARIO_DEFAULT_LIVE 4

#define HIDDEN_SCENE_1_X	6754
#define HIDDEN_SCENE_1_Y	270

#define MARIO_WALK_BEHIND_MAP_TIME 12000

#define MARIO_CENTER_POSITION_X	4577
#define MARIO_CENTER_POSITION_Y 867

using namespace std;

class CMario : public CGameObject
{
	int animation;
	int untouchable;
	ULONGLONG untouchable_start;

	int die;
	ULONGLONG die_start;

	int walkbehind;
	ULONGLONG walk_behind_start;

	// initial position of Mario at scene
	float start_x;
	float start_y;

	int live;
	int points;
	int level;
	int coins;

	vector<string> reward;
	Input input;
	void ResetAllFlags();
public:
	CMarioState* marioState;
	CMarioTail* tail;

	int powerLevel;

	bool isSitting ;
	bool canJumpHigh ;
	bool isStuckWithMiniGoomba;

	bool powerMode ;
	bool isFloating ;
	bool isJumpOnSwitch ;
	bool canGoIntoPipe ;
	bool canChangeMap ;
	bool canWalkBehindMap;
	bool isHoldKoopa;
	bool isOnRedMagicBlock ;
	bool isAutoWalk;
	bool isOnSpecialBox ;

	CMario(float x = 0.0f, float y = 0.0f);
	virtual void Update(DWORD dt, vector <LPGAMEOBJECT>* colliable_objects = NULL);
	virtual void Render();
	virtual void SetState(int state);

	void InitState();
	
	void ChangeState(CMarioState* new_state) { marioState = new_state;}
	CMarioState* GetState() { return marioState;}

	void SetLevel(int l) { level = l; }
	int GetLevel() { return level; };

	void SetLive(int lives) { live = lives; };
	int GetLive() { return live; };

	void SetPoints(int point) { this->points+= point; };
	int GetPoints() { return points; };

	void SetCoins() { this->coins += 1; };
	void SetCoins(int coin) { this->coins = coin; };
	int GetCoins() { return coins; };

	void SetReward(string r) { this->reward.push_back(r); };
	vector<string> GetReward() { return this->reward; };

	void LevelUp();
	void RecalculatePower();
	void SetAnimation(int ani) { animation = ani; }
	int GetCurrentAnimation() { return animation; }

	void StartUntouchable() { untouchable = 1; untouchable_start = GetTickCount64(); }
	void StartDie() { die = 1; die_start = GetTickCount64(); }

	void ResetUntouchable() { untouchable = 0; untouchable_start = 0; }
	void ResetDie() { die = 0; die_start = 0; }

	void ResetMario(int level);
	void SwitchOverworld();
	
	void SetInput(Input i) { this->input = i; };
	Input GetInput() { return this->input; };
 
	void LevelMarioDown();
	void HandleInput(Input input);

	void AttachTail(CMarioTail* tail) { this->tail = tail; };
	void CheckMarioOutOfCamera();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	void MovingMarioWithCamera();
	void AutoWalk();
	void StandOnPlatform() { isOnGround = true; isFloating = false;}

	void GoBackToNormalScene();
	void MoveToSecretScreen();

	void MoveToCenter();

	void WalkBehindStart() { walkbehind = 1; walk_behind_start = GetTickCount64(); }
	void ResetWalkBehind() { walkbehind = 0; walk_behind_start = 0; };
};


