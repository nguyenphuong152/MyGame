#include "Text.h"
#include "HUD.h"
#include "Sprites.h"
#include "Utils.h"
#include "Game.h"

CText::CText(Content content,float x, float y)
{
	this->content = content;
	start_x = x;
	start_y = y;

	default_time = 0;
	power = 0;
	flashing_start = 0;
	flashing = 0;
	size = 0;

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
	case Content::Noti:
		size = NOTI_TEXT_SIZE;
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
	if (content != Content::Noti)
	{
		int number = atoi(input.c_str());
		for (int i = 0; i < size; i++)
		{
			int a = number % 10;
			number = number / 10;
			letters[size - 1 - i].SetLetter(a);
			letters[i].SetPosition(start_x + HUD_BLANKSPACE * i, start_y, Content::Coin);
		}
	}
	else {
		int i = 0;

		if (input.compare("mushroom") == 0 || input.compare("whiteflower") == 0 || input.compare("star") == 0)
		{
			letters[i].SetLetter(input);
			letters[i].SetPosition(start_x , start_y, Content::Noti);
		}
		else {
			for (char& c : input)
			{
				string l;
				l.push_back(c);

				letters[i].SetLetter(l);
				letters[i].SetPosition(start_x + HUD_BLANKSPACE * i, start_y, Content::Noti);
				i++;
			}
		}
	}
}

void CText::SetPower(int number) {
	CMario* player = CGame::GetInstance()->GetPlayer();
	int powerLevel = player->powerLevel/100;

	for (int i = 0; i < number; i++)
	{
		if (i < powerLevel)
		{
			letters[i].SetLetter("arrowWhite");
		}
		else {
			letters[i].SetLetter("arrowBlack");
		}
		
		letters[i].SetPosition(start_x + HUD_BLANKSPACE * i, start_y, Content::Power);
		
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

	letters[size - 1].SetPosition(start_x + HUD_BLANKSPACE * (size-1), start_y,Content::Power);
}

void CText::Countdown()
{
	ULONGLONG countdown_start = HUD::GetInstance()->GetCountdownStart();
	default_time = GAME_TIME -(GetTickCount64() - countdown_start) / 1000;
	SetText(to_string(default_time));
}

void CText::SetLive()
{
	CMario* player = CGame::GetInstance()->GetPlayer();
	int live = player->GetLive();
	SetText(to_string(live));
}

/*Letter*/


Letter::Letter()
{
	x = y = 0.0f;
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
	if (CGame::GetInstance()->current_scene!=OVERWORLD_MAP)
	{
		CSprites::GetInstance()->Get(texture)->Draw(-1, 1, x, y);
	}
	else {
		CSprites::GetInstance()->Get(texture)->Draw(-1, 1, x+30, y);
	}
}

void Letter::SetPosition(float x, float y,Content type)
{
	if (type != Content::Noti)
	{
		float hud_x, hud_y;
		HUD::GetInstance()->GetPosition(hud_x, hud_y);
		this->x = floor(x + hud_x);
		this->y = floor(y + hud_y);
	}
	else {
		this->x = x;
		this->y = y;
	}
}

