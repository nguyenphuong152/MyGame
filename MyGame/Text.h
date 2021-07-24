#pragma once
#include <string>
#include "Utils.h"
#include "Mario.h"

#define WORLD_TEXT_SIZE 1
#define LIVE_TEXT_SIZE	1
#define POWER_TEXT_SIZE 7
#define POINT_TEXT_SIZE	7
#define TIME_TEXT_SIZE 3
#define COIN_TEXT_SIZE 2
#define NOTI_TEXT_SIZE 100

#define GAME_TIME 900
#define FLASHING_TIME 30
#define MAX_POWER 6

using namespace std;

enum class Content {
	World,
	Live,
	Point,
	Time,
	Coin,
	Power,
	Noti
};

class Letter {
	int texture = 0;
	float x, y;
public:
	Letter();
	void SetLetter(int letter);
	void SetLetter(string letter);
	void SetPosition(float x, float y, Content type);
	void Render();
};

class CText {
	Letter* letters;
	Content content;
	int size ;
	float start_x, start_y;

	ULONGLONG default_time ;
	int power;
	ULONGLONG flashing_start;
	int flashing ;
public:
	CText(Content content,float x,float y);
	
	void SetText(string text);
	void SetPower(int number);
	void Update();
	void RenderText();
	void RenderPower();
	void Countdown();
	void SetLive();
	void StartFlashing() { flashing_start = GetTickCount64(); flashing = 1; };
};

