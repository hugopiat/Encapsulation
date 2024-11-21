#include <SDL2/SDL.h>
#include "InputSystemSDL.h"
#include "WindowSDL.h"

void InputSystemSDL::PoolEvent()
{
    for (int i = 0; i < s_keys.size(); i++)
    {
        if (s_keys[i] == KeyState::KeyPressed)
        {
            s_keys[i] = KeyState::KeyDown;
        }
        if (s_keys[i] == KeyState::KeyReleased)
        {
            s_keys[i] = KeyState::KeyUp;
        }
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        int code = event.key.keysym.sym;

        switch (event.type)
        {

        case SDL_QUIT:
            WindowSDL::s_shouldClose = true;
            break;
        case SDL_KEYDOWN:
            if (s_keys[code] == KeyState::None || s_keys[code] == KeyState::KeyReleased || s_keys[code] == KeyState::KeyUp)
            {
                s_keys[code] = KeyState::KeyPressed;
            }
            break;
        case SDL_KEYUP:
            if (s_keys[code] == KeyState::None || s_keys[code] == KeyState::KeyDown || s_keys[code] == KeyState::KeyReleased)
            {
                s_keys[code] = KeyState::KeyReleased;
            }
            break;
        }
    }


}
