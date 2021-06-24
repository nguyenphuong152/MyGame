#pragma once
#include "GameObject.h"
#include "Mario.h"
#define POWER_UP_BBOX_WIDTH		40
#define POWER_UP_GRAVITY		0.003f

#define POWER_UP_ANI			0

#define SUPER_MUSHROOM_ANI		26
#define SUPER_LEAF_ANI			27

#define POWERUP_STATE_GO_UP		100
#define POWERUP_STATE_WALKING   200

#define LEAF_DEFLECT_SPEED		0.5f
#define LEAF_VELOCITY_X			0.3f

#define FLOATING_TIME			100

#define MUSHROOM_VELOCITY_X     0.1f
#define MUSHROOM_VELOCITY_Y		0.02f

enum class PowerUpType {
	none,
	super_leaf,
	super_mushroom
};

class CPowerUp : public CGameObject
{
	PowerUpType powerup_type;

	float start_y;

	int changeDirection = 0;
	int direction = 1;
	DWORD changeDirection_start;

	CMario* player;
public:
	bool isActive = false;
	CPowerUp(float x,float y);
	virtual void Render();
	virtual void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state) ;
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* colObject);

	void SetPowerUpType(PowerUpType type) { powerup_type = type; };
	PowerUpType GetPowerUpType() { return powerup_type; };
	void DefinePowerUpType();
	void SetStateForSuperMushroom();
	void SetStateForSuperLeaf();
	void HandleUpdateSuperLeaf();
	void HandleUpdateSuperMushroom();
	void ActivatePower() { isActive = true; };
    
	void StartChangeDirection() { changeDirection = 1; changeDirection_start = GetTickCount64(); }
};