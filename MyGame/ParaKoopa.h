#pragma once
#include "Koopas.h"

#define PARA_KOOPA_STATE_JUMPING	500

#define PARA_KOOPA_ANI_JUMPING	4

#define PARA_KOOPA_HIGH_JUMP_VELOCITY_Y		0.35f



class CParaKoopa : public CKoopas
{
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);
	virtual void Render();
public:
	CParaKoopa();
	virtual void SetState(int state);
};