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

    milliseconds newTick = duration_cast<milliseconds>(
        system_clock::now().time_since_epoch()
    );

    m_deltaTime += newTick.count() - m_lastTick;
    m_lastTick = newTick.count();
    if (m_deltaTime > 1000 / FPS_MAX)
    {
        if (m_deltaTime > 1000 / (FPS_MAX / 2))
        {
            m_deltaTime = 1000 / (FPS_MAX / 2);
        }
        m_haveToResetDeltaTime = true;
        m_deltaTime /= 1000;
        return true;
    }
    return false;
	return false;
}
