#pragma once
#include "GameObject.h"

#define PIPE_WIDTH 46

enum class PipeType {
	entry,
	exit,
	hidden_down,
	hidden_up
};

class CPipe : public CGameObject
{
	PipeType type;
public:
	CPipe(PipeType type);
	PipeType GetType() { return type; };
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
};

