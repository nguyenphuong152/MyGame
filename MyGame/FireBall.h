#include "GameObject.h"
#include "Mario.h"
#include "RedVenusFireTrap.h"

#define FIREBALL_POSITION_X 360
#define FIREBALL_POSITION_Y 339

#define FIREBALL_BBOX_WIDTH 14
#define FIREBALL_BBOX_HEIGHT 14

#define FIREBALL_STATE_FIRE 0
#define FIREBALL_VELOCITY_X 0.05f

#define FIREBALL_VELOCITY_Y_NEAR 0.8f
#define FIREBALL_VELOCITY_Y_FAR 0.4f

#define POSITION_CHANGE_VY 287

class CFireBall : public CGameObject
{
	CMario* player;
	//CRedVenusFireTrap* venus;

public:
	bool isShootingUp;
	CFireBall(CMario *player, bool isShootingUp);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject );
	void Render();
	virtual void SetState(int state);

	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

