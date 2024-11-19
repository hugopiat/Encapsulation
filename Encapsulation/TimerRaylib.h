#pragma once
#include "ATimer.h"
class TimerRaylib :
    public ATimer
{
    // Hérité via ATimer
    bool UpdateTime() override;
};

