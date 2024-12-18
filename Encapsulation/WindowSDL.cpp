#include "WindowSDL.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <iostream>
#include "Timer.h"

bool WindowSDL::s_shouldClose = false;

WindowSDL::WindowSDL()
{
    
    std::cout << "[SDL] On Create Window" << std::endl;
    m_isSdlInit = false;
    m_winSurface = nullptr;
    m_window = nullptr;
    m_renderer = nullptr;
}

void WindowSDL::Init()
{
    if (!InitLib())
        return;
    if (!CreateWindow())
        return;
    if (!InitRenderer())
        return;
    if (!GetSurface())
        return;

    TTF_Init();
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

bool WindowSDL::InitRenderer()
{
    m_renderer =
        SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer)
    {
        std::cerr << "SDL_CreateRenderer failed: " << SDL_GetError() << std::endl;
        return false;
    }

    int a = SDL_SetRenderDrawBlendMode(m_renderer, SDL_BLENDMODE_BLEND);
    int b = SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    std::cout << "[SDL] Create Window" << std::endl;

    return true;
}

bool WindowSDL::CreateWindow()
{
    m_window = 
        SDL_CreateWindow("[SDL] PROJECT : BLOCKS GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_width, m_height, SDL_WINDOW_SHOWN);

    if (!m_window) {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        // End the program
        return false;
    }
    
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
    SDL_RenderPresent(m_renderer);
}

void WindowSDL::Clear()
{
    //std::cout << "[SDL] Clear Window" << std::endl;
    SDL_RenderClear(m_renderer);
    //system("CLS");
}

bool WindowSDL::IsOpen()
{
    //std::cout << "[SDL] IsOpen Window" << std::endl;
    if (!m_isSdlInit)
    {
        return false;
    }

    return m_window && !s_shouldClose;
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

