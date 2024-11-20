#include "App.h"
#include "AWindow.h"
#include "Timer.h"
#include "Ball.h"

#if _SDL
#include <SDL2/SDL_timer.h>
#include "WindowSDL.h"
#include "SpriteSDL.h"
using SPECIFIC_WINDOW = WindowSDL;
using SPECIFIC_SPRITE = SpriteSDL;
#endif // _SDL

#if _RAYLIB
#include "WindowRaylib.h"
#include "SpriteRaylib.h"
using SPECIFIC_WINDOW = WindowRaylib;
using SPECIFIC_SPRITE = SpriteRaylib;
#endif // _RAYLIB


void App::Run()
{
    
    Init();
    while (m_window->IsOpen())
    {
        if (m_timer->UpdateTime())
        {
            Update(Timer::GetDeltaTime());
            Draw();      
        }
    }

    m_window->Close();
    DeleteBalls();
}

void App::Init()
{
    balls = std::vector<Ball*>();

    m_window = new SPECIFIC_WINDOW();
    m_sprite = new SPECIFIC_SPRITE();
    m_timer = new Timer();


    if (m_window == nullptr || m_timer == nullptr || m_sprite == nullptr)
    {
        return;
    }

    m_window->Init();
    m_sprite->Init(m_window, filename, 50, 50);

    SpawnBalls(5);
}

void App::Draw()
{
    m_window->Clear(); 
    
    for (int i = 0; i < balls.size(); i++) 
    {
        balls[i]->Draw();
    }

    m_window->Draw();
}

void App::Update(float deltaTime)
{
    for (int i = 0; i < balls.size(); i++) {
        balls[i]->Update(deltaTime, m_window->m_width, m_window->m_height);
    }
}

void App::SpawnBalls(int count)
{
    std::srand(static_cast<unsigned>(std::time(0)));
    for (int i = 0; i < count; ++i) {
        float posX = std::rand() % 800;
        float posY = std::rand() % 600;
        float directionX = (std::rand() % 10) - 5; // Vitesse entre -5 et 5
        float directionY = (std::rand() % 10) - 5;

        Ball* ball = new Ball();
        ball->Init(Maths::Vector2(posX, posY), Maths::Vector2(directionX, directionY), m_sprite);
        ball->SetSpeed(100.0f);
        balls.push_back(ball);
    }
}

void App::DeleteBalls() 
{
    // Lib�ration de la m�moire
    for (int i = 0; i < balls.size(); i++) {
        delete balls[i];
    }
    delete m_window;
    delete m_sprite;
}
