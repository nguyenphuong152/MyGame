#pragma once
#include <string>

using namespace std;

class CLetter {
	float x, y;
	string name;
	int texture;
public:
	CLetter(string name, int texture);
	void Render();
	void SetPosition(float x, float y);
};