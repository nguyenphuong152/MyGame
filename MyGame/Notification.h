#pragma once
#include "Text.h"
#include "Reward.h"

#define FIRST_LINE_TIME 300
#define SECOND_LINE_TIME 4000

class CNotification {
	vector<CText*> content;
	static CNotification* __instance;
	reward re;

	int firstLine = 0;
	ULONGLONG firstLine_start = 0;

	int secondLine = 0;
	ULONGLONG secondLine_start = 0;

	void FirstLineStart() { firstLine = 1; firstLine_start = GetTickCount64(); };
	void ResetFirstLine() { firstLine = 0; firstLine_start = 0; };

	void SecondLineStart() { secondLine = 1; secondLine_start = GetTickCount64(); };
	void ResetSecondLine() { secondLine = 0; secondLine_start = 0; };

	string ClassifyReward(int reward);
public:
	bool visible = false;

	static CNotification* GetInstance();
	void Init(int reward);
	void Update();
	void Render();
	CText* SetContent(string c, float x, float y);
	void ShowNoti(int reward);

	void Clear();
};