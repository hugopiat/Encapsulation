#pragma once
#include "ATimer.h"

class TimerSDL : public ATimer
{
public:
	// H�rit� via ATimer
	bool UpdateTime() override;
};

