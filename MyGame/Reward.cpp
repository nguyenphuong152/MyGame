#include "Reward.h"
#include "Animations.h"
#include "Utils.h"
#include "Game.h"

Reward::Reward(reward t)
{
	flashing = 0;
	flashing_start = 0;
	isEnable = true;
	SetAnimation(REWARD_ANIMATION_SETS);
	type = t;
	SetState(STATE_FLASHING);
	StartFlashing();
}

int Reward::GetAnimation(int state, reward type)
{
	int ani = -1;
	if (state == STATE_FLASHING)
	{
		if (type == reward::mushroom) ani = MUSHROOM_FLASHING;
		else if (type == reward::star) ani = STAR_FLASHING;
		else ani = WHITE_FLOWER_FLASHING;
	}
	else if (state == STATE_NORMAL)
	{
		if (type == reward::mushroom) ani = MUSHROOM;
		else if (type == reward::star) ani = STAR;
		else ani = WHITE_FLOWER;
	}
	return ani;
}

void Reward::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = t = r = b = 0;
}

void Reward::Update()
{
	if ((flashing == 1 && GetTickCount64() - flashing_start > REWARD_FLASHING_TIME)
		|| (CGame::GetInstance()->current_scene == OVERWORLD_MAP))
		SetState(STATE_NORMAL);
}

void Reward::Render()
{
	int ani = GetAnimation(state, type);
	if (CGame::GetInstance()->current_scene == OVERWORLD_MAP)
	{
		animation_set->at(ani)->Render(1, 1,x + 28, y);
	}
	else {
		animation_set->at(ani)->Render(1, 1, x, y);
	}
	
}
