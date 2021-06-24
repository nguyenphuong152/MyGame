#pragma once

#include "GameObject.h"

#define PORTAL_BBOX 48

/*
	Object that triggers scene switching
*/

class CPortal : public CGameObject
{
	int scene_id; //target scene to switch
	int texture;

public:
	CPortal(int texture,int scene_id);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	int GetSceneId() { return scene_id; }


};

