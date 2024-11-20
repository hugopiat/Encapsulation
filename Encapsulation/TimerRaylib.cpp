#include <ctime>
#include "TimerRaylib.h"
#include "raylib.h"
bool TimerRaylib::UpdateTime()
{
    m_deltaTime = GetFrameTime();
    return true;
}
