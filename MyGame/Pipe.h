#pragma once
#include "GameObject.h"

#define PIPE_WIDTH 84

enum class PipeType {
	entry,
	exit,
	hidden,
};

class CPipe : public CGameObject
{
	float width, height;
public:
	PipeType type;
	CPipe(PipeType type, float width, float height);
	PipeType GetType() { return type; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

