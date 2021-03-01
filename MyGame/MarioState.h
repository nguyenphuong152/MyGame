#pragma once
class CMarioStateIdle;
class CMarioStateWalk;
class CMarioStateJump;
class CMarioStateSit;
class CMarioStateStop;
class CMarioStateRun;
class CMarioStatePreFly;
class CMarioStateFly;
class CMarioStateSpin;
class CMarioStateDrop;
class CMarioStateKick;
class CMarioStateHoldShellIdle;
class CMarioStateHoldShellAndRun;
class CMarioStateHoldShellAndJump;
class CMarioStateHoldShellAndDrop;


#include "Utils.h"
#include <dinput.h>
#include "Game.h"
#include "Input.h"

class CMarioState
{
	friend class CMario;
public:
	enum MarioStates {
		IDLE,
		WALK,
		JUMP,
		SIT,
		STOP,
		RUN,
		PRE_FLY,
		FLY,
		FLOAT,
		SPIN,
		DROP,
		KICK,
		HOLDSHELL_IDLE,
		HOLDSHELL_RUN,
		HOLDSHELL_JUMP,
		HOLDSHELL_DROP
	};

	static CMarioStateIdle idle;
	static CMarioStateWalk walk;
	static CMarioStateJump jump;
	static CMarioStateSit sit;
	static CMarioStateStop stop;
	static CMarioStateRun run;
	static CMarioStatePreFly pre_fly;
	static CMarioStateFly fly;
	static CMarioStateSpin spin;
	static CMarioStateDrop drop;
	static CMarioStateKick kick;
	static CMarioStateHoldShellIdle holdshell_idle;
	static CMarioStateHoldShellAndRun holdshell_run;
	static CMarioStateHoldShellAndJump holdshell_jump;
	static CMarioStateHoldShellAndDrop holdshell_drop;

	CMarioState();
	//CMarioState(CMarioState::MarioStates currentState);
	virtual ~CMarioState() {};

	CMarioState::MarioStates GetCurrentState();
	void SetCurrentState(CMarioState::MarioStates current_state);

	virtual void Enter(CMario& mario) = 0;
	virtual void HandleInput(CMario& mario, Input input) = 0;
	virtual void Update(DWORD dt,CMario& mario) = 0;
	

protected:
	CMarioState::MarioStates currentState;
};

