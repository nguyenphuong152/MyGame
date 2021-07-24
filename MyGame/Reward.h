#pragma once
#include "GameObject.h"

#define REWARD_ANIMATION_SETS	53
#define MUSHROOM_FLASHING		0
#define MUSHROOM				1
#define STAR_FLASHING			2
#define STAR					3
#define WHITE_FLOWER_FLASHING	4
#define WHITE_FLOWER			5
#define STATE_FLASHING			100
#define STATE_NORMAL			200

#define REWARD_FLASHING_TIME			3000

enum class reward {
	none,
	star,
	flower,
	mushroom
};

class Reward : public CGameObject{
	reward type;

	int flashing;
	ULONGLONG flashing_start;

	int GetAnimation(int state, reward type);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);

	void StartFlashing() { flashing = 1; flashing_start = GetTickCount64(); };
	void ResetFlashing() { flashing = 0; flashing_start = 0; };
public:
	Reward(reward t);
	void Update();
	void Render();
};