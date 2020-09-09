#pragma once

#include <Windows.h>
#include <d3dx9.h>
#include <unordered_map>

#include "Sprites.h"

class CAniFrame
{
	LPSPRITE sprite;
	DWORD time;

public:
	CAniFrame(LPSPRITE sprite, int time) { this->sprite = sprite; this->time = time; }
	DWORD GetTime() { return time; }
	LPSPRITE GetSprite() { return sprite; }

};

typedef CAniFrame* LPANIMATION_FRAME;

class CAnimation
{
	DWORD lastFrameTime;
	int currentFrame;
	int defaultTime;
	vector<LPANIMATION_FRAME> frames;

public:
	CAnimation(int defaultTime = 100) {
		this->defaultTime = defaultTime;lastFrameTime = -1; currentFrame = -1;
	}
	void Add(int spriteId, DWORD time = 0);

	void Render(float x, float y, int alpha = 255);
};


typedef CAnimation* LPANIMATION;

class CAnimations
{
	static CAnimations* _instance;

	unordered_map<int, LPANIMATION> animations;

public:
	void Add(int id, LPANIMATION ani);
	LPANIMATION Get(int id);
	void Clear();

	static CAnimations* GetInstance();

};

typedef vector<LPANIMATION> CAnimationSet;
typedef CAnimationSet* LPANIMATION_SET;

/*Manage animation set database*/

class CAnimationSets
{
	static CAnimationSets* _instance;
	unordered_map<int, LPANIMATION_SET> animation_sets;

public:
	CAnimationSets();
	void Add(int id, LPANIMATION_SET ani);
	LPANIMATION_SET Get(unsigned int id);

	static CAnimationSets* GetInstance();
};


