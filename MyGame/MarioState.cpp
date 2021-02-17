#include "MarioState.h"

CMarioState::CMarioState()
{
	//this->currentState = CMarioState::IDLE;
}

//CMarioState::CMarioState(CMarioState::MarioStates currentState)
//{
//	this->currentState = currentState;
//}



CMarioState::MarioStates CMarioState::GetCurrentState()
{
	return this->currentState;
}

void CMarioState::SetCurrentState(CMarioState::MarioStates current_state)
{
	this->currentState = current_state;
}


