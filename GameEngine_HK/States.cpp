#include "States.h"


bool States::bIsPaused = false;


bool States::GetPausedState()
{
	return bIsPaused;
}

void States::SetPausedState(bool bBooleanState)
{
	bIsPaused = bBooleanState;
}
