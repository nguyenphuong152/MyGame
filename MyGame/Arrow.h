#pragma once
#include "GameObject.h"

#define ARROW_ANI 65

class CArrow : public CGameObject {
public:
	bool startGame;
	float start_y;
	CArrow();
	void MoveUp();
	void MoveDown();
	void StartGame();
	virtual void Render();
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObjects);
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};