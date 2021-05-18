#include "Text.h"
#include "HUD.h"
#include "Sprites.h"
#include "Utils.h"
#include "Mario.h"

CText::CText(Content content,float x, float y)
{
	this->content = content;
	start_x = x;
	start_y = y;

	switch (content)
	{
	case Content::Live:
		size = LIVE_TEXT_SIZE;
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
	case Content::Coin:
		size = COIN_TEXT_SIZE;
		break;
	case Content::Power:
		size = POWER_TEXT_SIZE;
		break;
	}

	letters = new Letter[size];
}

void CText::Update()
{
	switch (content)
	{
	case Content::Live:
		SetLive();
		break;
	case Content::World:
		SetText("1");
		break;
	case Content::Point:
		SetText("999999");
		break;
	case Content::Time:
		Countdown();
		break;
	case Content::Coin:
		SetText("30");
		break;
	case Content::Power:
		SetPower(MAX_POWER);
		power = MAX_POWER;
		break;
	}
}

void CText::RenderText()
{
	for (int i = 0; i < size; i++)
	{
		letters[i].Render();
	}
}

void CText::RenderPower()
{
	for (int i = 0; i < power; i++)
	{
		letters[i].Render();
	}
	letters[size - 1].Render();
}


void CText::SetText(string input)
{
	int number = atoi(input.c_str());
	for (int i = 0; i < size; i++)
	{
		int a = number % 10;
		number = number / 10;
		letters[size - 1 - i].SetLetter(a);
		letters[i].SetPosition(start_x + HUD_BLANKSPACE * i, start_y);
	}
}

void CText::SetPower(int number) {
	int powerLevel = CMario::GetInstance()->powerLevel/100;

	for (int i = 0; i < number; i++)
	{
		if (i < powerLevel)
		{
			letters[i].SetLetter("arrowWhite");
		}
		else {
			letters[i].SetLetter("arrowBlack");
		}
		
		letters[i].SetPosition(start_x + HUD_BLANKSPACE * i, start_y);
		
	}

	if (powerLevel == MAX_POWER+1 && flashing == 0)
	{
		letters[size - 1].SetLetter("powerWhite");
		StartFlashing();
	}
	else {
		letters[size - 1].SetLetter("powerBlack");
	}

	if (flashing == 1&&GetTickCount64()- flashing_start>FLASHING_TIME)
	{
		letters[size - 1].SetLetter("powerBlack");
		flashing = 0;
	}

	letters[size - 1].SetPosition(start_x + HUD_BLANKSPACE * (size-1), start_y);
}

void CText::Countdown()
{
	int now = GetTickCount64();
	int countdown_start = HUD::GetInstance()->GetCountdownStart();
	default_time = GAME_TIME-(now - countdown_start) / 1000;
	SetText(to_string(default_time));
}

void CText::SetLive()
{
	int live = CMario::GetInstance()->GetLive();
	SetText(to_string(live));
}

void Letter::SetLetter(int letter)
{
	string l = to_string(letter);
	int tex = HUD::GetInstance()->GetTextureOfLetter(l);
	if (tex != NULL) texture = tex;
}

void Letter::SetLetter(string letter)
{
	int tex = HUD::GetInstance()->GetTextureOfLetter(letter);
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