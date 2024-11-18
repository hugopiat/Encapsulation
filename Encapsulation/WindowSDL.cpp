#if _SDL
#include <iostream>
#include "WindowSDL.h"

void WindowSDL::OnCreate()
{
    std::cout << "[SDL] On Create Window" << std::endl;
}

void WindowSDL::Init()
{
    std::cout << "[SDL] Init Window" << std::endl;
}

void WindowSDL::Draw()
{
    std::cout << "[SDL] Draw Window" << std::endl;
}

void WindowSDL::Clear()
{
    std::cout << "[SDL] Clear Window" << std::endl;
}

bool WindowSDL::IsOpen()
{
    std::cout << "[SDL] IsOpen Window" << std::endl;
    return false;
}

#endif // _SDL