#pragma once
#include "StateTest.h"
#include <dinput.h>

void Test::HandleOnKeyDown(int KeyCode)
{

	if (KeyCode == DIK_A)
	{

		DebugOut(L"[INFO] Key Down code! %d \n", KeyCode);
	}

}

void Test::HandleOnKeyUp(int KeyCode) {
	DebugOut(L"[INFO] Key Up code! %d \n", KeyCode);
}

void Test::HandleKeyState(BYTE* states) {
	//DebugOut(L"[INFO] Key state %d",states);
}