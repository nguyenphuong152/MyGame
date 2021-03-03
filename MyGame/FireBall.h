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
private:
	CMario* player;
	int _timeLeft;
	union {
		//state when it's use
		struct 
		{
			float x, y;
		} live ;
		//state when it's available
		CFireBall* next;
	} _state;

public:
	friend class FireBallPool;

	CFireBall* GetNext() const { return _state.next; }
	void SetNext(CFireBall* fireball){
		_state.next = fireball;
	}

	void Init(float x, float y, int lifeTime);
	bool inUse() const { return _timeLeft > 0; }
	bool Animate();

	bool isShootingUp;
	
	CFireBall(CMario *player, bool isShootingUp);
	virtual void Update(DWORD dt, vector<LPGAMEOBJECT>* coObject );
	void Render();
	virtual void SetState(int state);
	virtual void GetBoundingBox(float& left, float& top, float& right, float& bottom);
};

