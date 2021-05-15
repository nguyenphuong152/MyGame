#include "LetterManager.h"

CLetterManager* CLetterManager::__instance = NULL;

CLetterManager* CLetterManager::GetInstance()
{
	if (__instance == NULL) __instance = new CLetterManager();
	return __instance;
}

void CLetterManager::AddLetter(string name, int texture)
{
	LPLETTERS l = new CLetter(name,texture);
	letters[name] = l;
}
