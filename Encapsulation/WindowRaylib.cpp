#include "WindowRaylib.h"
#include "raylib.h"
#include "Timer.h"

void WindowRaylib::Init()
{
    // m_width *= 1.25f;
    // m_height *= 1.25f;

    InitWindow(m_width, m_height, "[RAYLIB] PROJECT: BLOCKS GAME");    
    SetTargetFPS(FPS_MAX);
}

void WindowRaylib::Draw()
{
    EndDrawing();
}

void WindowRaylib::Clear()
{
    BeginDrawing();
    ClearBackground(BLACK);
}

bool WindowRaylib::IsOpen()
{
    return !WindowShouldClose();
}

bool WindowRaylib::Close()
{
    CloseWindow();
    return true;
}
