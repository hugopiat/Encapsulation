#if _SDL
#include <iostream>
#include <SDL2/SDL.h>
#include "WindowSDL.h"


WindowSDL::WindowSDL()
{
    m_isSdlInit = false;
    m_winSurface = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;
    std::cout << "[SDL] On Create Window" << std::endl;

}

void WindowSDL::Init()
{
    if (!InitLib())
        return;
    if (!CreateWindow())
        return;
    if (!GetSurface())
        return;

    SDL_FillRect(m_winSurface, NULL, SDL_MapRGB(m_winSurface->format, 255, 255, 255));
}

bool WindowSDL::InitLib()
{
    if (m_isSdlInit)
    {
        return true;
    }

    // Initialize SDL. SDL_Init will return -1 if it fails.
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        m_isSdlInit = false;
        return m_isSdlInit;
    }

    std::cout << "[SDL] Init Window" << std::endl;
    m_isSdlInit = true;
    return m_isSdlInit;
}

bool WindowSDL::CreateWindow()
{
    m_window = 
        SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);

    if (!m_window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        return false;
    }

    m_renderer = 
        SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "[SDL] Create Window" << std::endl;
    return true;
}

bool WindowSDL::GetSurface()
{
    m_winSurface = SDL_GetWindowSurface(m_window);

    // Make sure getting the surface succeeded
    if (!m_winSurface) {
        std::cout << "Error getting surface: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        return false;
    }

    return true;
}

void WindowSDL::Draw()
{
    SDL_UpdateWindowSurface(m_window);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(16);
    std::cout << "[SDL] Draw Window" << std::endl;
}

void WindowSDL::Clear()
{
    SDL_RenderClear(m_renderer);
    std::cout << "[SDL] Clear Window" << std::endl;
}

bool WindowSDL::IsOpen()
{
    if (!m_isSdlInit)
    {
        return false;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return false;
            break;

        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                return false;
            }
            break;
        }
    }

    std::cout << "[SDL] IsOpen Window" << std::endl;
    return m_window;
}

bool WindowSDL::Close()
{
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
    return true;
}

SDL_Renderer* WindowSDL::GetRenderer()
{
    return m_renderer;
}

#endif // _SDL