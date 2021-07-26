#include "Mario.h"
#include "MarioStateJump.h"
#include "MarioStateDrop.h"
#include "MarioStateThrowingFireballJumping.h"
#include "MarioStateGetIntoPipe.h"
#include "FireBall.h"
#include "FireBallPool.h"


CMarioStateJump* CMarioStateJump::__instance = NULL;

CMarioStateJump::CMarioStateJump() {
	jumpOnMagicNote = false;
	_jumpingStart = 0;
	DebugOut(L"[STATE] create jump \n");
}

void CMarioStateJump::Enter(CMario& mario)
{
	mario.isOnGround = false;
	int marioLevel = mario.GetLevel();
	if (marioLevel == MARIO_LEVEL_SMALL)
	{
		mario.SetAnimation(MARIO_ANI_SMALL_JUMP);
	}
	else if(marioLevel == MARIO_LEVEL_RACOON) {
		mario.SetAnimation(MARIO_ANI_RACCOON_JUMP);
	}
	else if (marioLevel == MARIO_LEVEL_IMMORTAL)
	{
		mario.SetAnimation(MARIO_ANI_IMMORTAL_JUMP);
	}
	else if (marioLevel == MARIO_LEVEL_FIRE)
	{
		mario.SetAnimation(MARIO_ANI_FIRE_JUMP);
	}
	else {
		mario.SetAnimation(MARIO_ANI_BIG_JUMP);
	}
}
void CMarioStateJump::HandleInput(CMario& mario,Input input)
{

	if (input == Input::RELEASE_S )
	{
		mario.canJumpHigh = false;
	}
	else if (input == Input::PRESS_A && mario.GetLevel() == MARIO_LEVEL_FIRE)
	{
		CFireball* fireball = CFireBallPool::GetInstance()->Create();
		if (fireball != NULL)
		{
			mario.ChangeState(CMarioState::throw_fireball_jump.GetInstance());
			fireball->AllocateFireballToMario();
			CMarioState::throw_fireball_jump.GetInstance()->StartThrowing();
		}
	}
	else
	{
		CMarioOnAirStates::HandleInput(mario, input);
	}
}

void CMarioStateJump::Update(DWORD dt, CMario& mario)
{
	 if (mario.canJumpHigh)
	{
		if (GetTickCount64() - _jumpingStart > MARIO_JUMP_TIME)
		{
			mario.canJumpHigh = false;
		}
		else if(mario.isOnRedMagicBlock){
			mario.vy = -2.0f;
		}
		else if (mario.isStuckWithMiniGoomba)
		{
			mario.vy = -0.1f;
		}
		else {
			mario.vy = -MARIO_JUMP_SPEED_Y;
		}
	}
	else if( mario.vy>0 )
	{
		mario.ChangeState(CMarioState::drop.GetInstance());
	}
}

CMarioStateJump* CMarioStateJump::GetInstance()
{
	if (__instance == NULL) __instance = new CMarioStateJump();
	return __instance;
}
