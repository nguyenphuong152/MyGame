#pragma once
#include "Text.h"

class CNotification {
	vector<CText*> content;
	static CNotification* __instance;

	int firstLine;
	ULONGLONG firstLine_start;

	int secondLine;
	ULONGLONG secondLine_start;

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