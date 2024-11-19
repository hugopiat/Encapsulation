#include "WindowRaylib.h"
#include "raylib.h"



void WindowRaylib::Init()
{
    const int screenWidth = m_width;
    const int screenHeight = m_height;

    InitWindow(screenWidth, screenHeight, "PROJECT: BLOCKS GAME");
    
    SetTargetFPS(60);
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
