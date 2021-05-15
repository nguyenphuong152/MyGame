#include "Text.h"
#include "HUD.h"
#include "Sprites.h"
#include "Utils.h"

CText::CText(Content content,float x, float y)
{
	this->content = content;
	start_x = x;
	start_y = y;

	switch (content)
	{
	case Content::Live:
		size = WORLD_TEXT_SIZE;
		break;
	case Content::World:
		size = WORLD_TEXT_SIZE;
		break;
	case Content::Point:
		size = POINT_TEXT_SIZE;
		break;
	case Content::Time:
		size = TIME_TEXT_SIZE;
		break;
	}

	letters = new Letter[size];
}

void CText::Update()
{
	if (content == Content::World)
	{
		SetText("1");
	}
	else if (content == Content::Live)
	{
		SetText("9");
	}
	else if (content == Content::Time)
	{
		Countdown();
	}
}

void CText::RenderText()
{
	for (int i = 0; i < size; i++)
	{
		letters[i].Render();
	}
}

void CText::SetText(string input)
{
	int number = atoi(input.c_str());
	for (int i = 0; i < size; i++)
	{
		int a = number % 10;
		number = number / 10;
		letters[size - 1 - i].SetLetter(a);
		letters[i].SetPosition(start_x + HUD_WHITE_SPACE * i, start_y);
	}
}

void CText::Countdown()
{
	int now = GetTickCount64();
	int countdown_start = HUD::GetInstance()->GetCountdownStart();
	default_time = GAME_TIME-(now - countdown_start) / 1000;
	SetText(to_string(default_time));
}


void Letter::SetLetter(int letter)
{
	string l = to_string(letter);
	int tex = HUD::GetInstance()->GetTextureOfLetter(l);
	if (tex != NULL) texture = tex;
}

void Letter::Render()
{
	CSprites::GetInstance()->Get(texture)->Draw(-1, 1, x, y);
}

void Letter::SetPosition(float x, float y)
{
	float hud_x, hud_y;
	HUD::GetInstance()->GetPosition(hud_x, hud_y);
	this->x = floor(hud_x + x);
	this->y = floor(hud_y + y);
}