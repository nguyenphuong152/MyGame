#include "MarioHoldingShellStates.h"
#include "MarioStateHoldShellAndRun.h"
#include "Mario.h"

CMarioHoldingShellStates::CMarioHoldingShellStates()
{
}

void CMarioHoldingShellStates::HandleInput(CMario& mario, Input input)
{
	CGame* game = CGame::GetInstance();
	if (game->IsKeyDown(DIK_LEFT))
	{
		//thiếu xoay qua phảo thắng lại miếng r chạy tiếp
		mario.SetDirection(DIRECTION_RIGHT_TO_LEFT);
		mario.SetVelocityX(-0.25);
		mario.ChangeState(CMarioState::holdshell_run.GetInstance());
	}
	else if (game->IsKeyDown(DIK_RIGHT))
	{
		mario.SetDirection(DIRECTION_LEFT_TO_RIGHT);
		mario.SetVelocityX(0.25);
		mario.ChangeState(CMarioState::holdshell_run.GetInstance());
	}

	if (input == Input::RELEASE_A)
	{
		mario.isKicking = true;
	}
}



