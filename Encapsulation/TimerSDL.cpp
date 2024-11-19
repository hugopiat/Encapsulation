#include <SDL2/SDL_timer.h>
#include "TimerSDL.h"

bool TimerSDL::UpdateTime()
{
    if (m_haveToResetDeltaTime)
    {
        m_deltaTime = 0;
        m_haveToResetDeltaTime = false;
    }

    unsigned int newTick = SDL_GetTicks();
    m_deltaTime += newTick - m_lastTick;
    m_lastTick = newTick;
    if (m_deltaTime > 1000/FPS_MAX)
    {
        m_haveToResetDeltaTime = true;
        return true;
    }
    return false;
}
