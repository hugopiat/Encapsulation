#pragma once
#include "ATimer.h"

class TimerSDL : public ATimer
{
public:
	// Hérité via ATimer
	bool UpdateTime() override;
};

