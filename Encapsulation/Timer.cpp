#include <chrono>
#include "Timer.h"

using namespace std::chrono;

float Timer::m_deltaTime = 0;

float Timer::GetDeltaTime()
{
	return m_deltaTime;
}

bool Timer::UpdateTime()
{
    if (m_haveToResetDeltaTime)
    {
        m_deltaTime = 0;
        m_haveToResetDeltaTime = false;
    }

    long long newTick = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    ).count() ;
    
    unsigned int diffTick = newTick - m_lastTick;
    m_deltaTime += diffTick / (float)1000;
    m_lastTick = newTick;
    if (m_deltaTime > 1.f / FPS_MAX)
    {
        if (m_deltaTime > 1.f / FPS_MIN)
        {
            m_deltaTime = 1.f / FPS_MIN;
        }
        m_haveToResetDeltaTime = true;
        return true;
    }
    return false;
}
