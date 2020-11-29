#pragma once
class States
{
private:
	static bool bIsPaused;

public:
	static bool GetPausedState();
	static void SetPausedState(bool bBooleanState);
};

