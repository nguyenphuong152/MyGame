#pragma once
#include "GameObject.h" 

enum class Type {
	Tree,
	Help,
	M,
};

class CDecoration : public CGameObject
{
	Type type;
public:
	CDecoration(Type type);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};