#pragma once
#include "ATimer.h"
class TimerRaylib :
    public ATimer
{
    // H�rit� via ATimer
    bool UpdateTime() override;
};

