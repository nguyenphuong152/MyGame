#pragma once
#include "Letter.h"
#include <unordered_map>

using namespace std;

typedef CLetter* LPLETTERS;

class CLetterManager
{
	static CLetterManager* __instance;
	unordered_map<string, LPLETTERS> letters;
public:
	static CLetterManager* GetInstance();
	void AddLetter(string name,int texture);
	void Render(string name);
	LPLETTERS GetLetterTexture(string name) { return letters[name]; };
};