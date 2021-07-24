#include "Notification.h"
#include "Card.h"
#include "Game.h"
#include "HUD.h"

CNotification* CNotification::__instance = NULL;

string CNotification::ClassifyReward(int reward)
{
	string name;
	CMario* player = CGame::GetInstance()->GetPlayer();
	if (reward == MUSHROOM_CARD) {
		re = reward::mushroom;
		name = "mushroom";
	}
	else if (reward == STAR_CARD) {
		re = reward::star;
		name = "star";
	}
	else {
		re = reward::flower;
		name = "whiteflower";
	}
	player->SetReward(name);
	
	return name;
}

CNotification* CNotification::GetInstance()
{
	if (__instance == NULL) __instance = new CNotification();
	return __instance;
}

void CNotification::Init(int reward)
{
   string reward_name = ClassifyReward(reward);

   CText* t1 = 	SetContent("course clear", FIRST_LINE_POS_X -1000, FIRST_LINE_POS_Y);
   CText* t2 = SetContent("you got a card", SECOND_LINE_POS_X -1000, SECOND_LINE_POS_Y);
   CText* t3 = SetContent(reward_name, REWARD_POS_X -1000, SECOND_LINE_POS_Y-20);

   content.push_back(t1);
   content.push_back(t2);
   content.push_back(t3);
}

void CNotification::Update()
{
	if (firstLine == 1 && GetTickCount64() - firstLine_start > FIRST_LINE_TIME)
	{
		ResetFirstLine();
		SecondLineStart();
		HUD::GetInstance()->AddReward(re);
	}
	if (secondLine == 1 && GetTickCount64() - secondLine_start > SECOND_LINE_TIME)
	{
		ResetSecondLine();
		CGame::GetInstance()->GetPlayer()->SwitchOverworld();
	}
}

void CNotification::Render()
{
	DebugOut(L"HUD %f %f \n", content[0]->start_x, content[0]->start_y);
	content[0]->RenderText();
	if (secondLine == 1)
	{
		content[1]->RenderText();
		content[2]->RenderText();
	}
}

CText* CNotification::SetContent(string c, float x, float y)
{
		CText* text = new CText(Content::Noti, x, y);
		text->SetText(c);
		return text;
}

void CNotification::ShowNoti(int reward)
{
	DebugOut(L"helo \n");
	Init(reward);
	visible = true;
	FirstLineStart();
}

void CNotification::Clear()
{
	visible = false;
	for (auto x : content)
	{
		if (x != NULL) delete x;
	}

	content.clear();
}
