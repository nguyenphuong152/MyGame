#pragma once
class CMarioStateIdle;
class CMarioStateWalk;
class CMarioStateJump;
class CMarioStateSit;
class CMarioStateStop;
#include "Utils.h"
#include <dinput.h>
#include "Game.h"

class CMarioState
{
	friend class CMario;
public:
	enum MarioStates {
		IDLE,
		WALK,
		JUMP,
		SIT,
		STOP
	};
	static CMarioStateIdle idle;
	static CMarioStateWalk walk;
	static CMarioStateJump jump;
	static CMarioStateSit sit;
	static CMarioStateStop stop;
	CMarioState();
	//CMarioState(CMarioState::MarioStates currentState);
	virtual ~CMarioState() {};

	CMarioState::MarioStates GetCurrentState();
	void SetCurrentState(CMarioState::MarioStates current_state);

	virtual void Enter(CMario& mario) = 0;
    virtual void HandleInput(CMario &mario) = 0;
	virtual void Update(DWORD dt,CMario& mario) = 0;
	

protected:
	CMarioState::MarioStates currentState;
};

