#include <ctime>
#include "TimerRaylib.h"
bool TimerRaylib::UpdateTime()
{

    int newTick = time(NULL);
    m_deltaTime = (newTick - m_lastTick);
    m_lastTick = newTick;
    return true;
}
