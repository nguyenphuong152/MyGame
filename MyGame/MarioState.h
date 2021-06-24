#pragma once
class CMarioStateIdle;
class CMarioOverworldState;
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
class CMarioStateTransform;
class CMarioStateGetIntoPipe;
class CMarioStateThrowFireballJumping;
class CMarioStateThrowFireball;
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
	static CMarioStateTransform transform;
	static CMarioStateGetIntoPipe go_to_pipe;
	static CMarioStateThrowFireballJumping throw_fireball_jump;
	static CMarioStateThrowFireball throw_fireball;
	static CMarioStateHoldShellIdle holdshell_idle;
	static CMarioStateHoldShellAndRun holdshell_run;
	static CMarioStateHoldShellAndJump holdshell_jump;
	static CMarioStateHoldShellAndDrop holdshell_drop;
	static CMarioOverworldState walking_overworld;

	CMarioState();
	virtual ~CMarioState() {};

	virtual void Enter(CMario& mario) = 0;
	virtual void HandleInput(CMario& mario, Input input) = 0;
	virtual void Update(DWORD dt,CMario& mario) = 0;

};

