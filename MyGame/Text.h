#pragma once
#include <string>

#define WORLD_TEXT_SIZE 1
#define POINT_TEXT_SIZE	7
#define TIME_TEXT_SIZE 3

#define GAME_TIME 900

using namespace std;

enum class Content {
	World,
	Live,
	Point,
	Time
};

class Letter {
	float x, y;
	int texture;
public:
	void SetLetter(int letter);
	void SetPosition(float x, float y);
	void Render();
	void Update();
};

class CText {
	Letter* letters;
	Content content;
	int size;
	float start_x, start_y;

	int default_time;

public:
	CText(Content content,float x,float y);
	void SetText(string text);
	void Update();
	void RenderText();
	void Countdown();
};

