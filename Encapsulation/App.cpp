#include "App.h"
#include "AWindow.h"
#include "Timer.h"
#include "Ball.h"

#include <SDL2/SDL_timer.h>
#include "WindowSDL.h"
#include "SpriteSDL.h"

#include "WindowRaylib.h"
#include "SpriteRaylib.h"


void App::Run(int argc, char* argv[])
{
    if (!ManageArgs(argc, argv))
    {
#if _SDL
        m_graphicLibType = GraphicLib::SDL2;
#elif _RAYLIB
        m_graphicLibType = GraphicLib::RAYLIB;
#else
        std::cout << "Il manque des arguments ou ceux specifies ne sont pas valides" << std::endl;
        return;
#endif // _RAYLIB
    }
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

bool App::ManageArgs(int argc, char* argv[])
{
    if (argc == 1)
    {
        return false;
    }
    m_graphicLibType = GraphicLib::NONE;
    std::string arg;
    for (int i = 1; i < argc; i++)
    {
        arg = argv[i];
        if (!PerformArgForGraphicLib(arg))
        {
            return false;
        }
    }

    if (m_graphicLibType == GraphicLib::NONE)
    {
        return false;
    }
    return true;
}

bool App::PerformArgForGraphicLib(const std::string& arg)
{
    if (m_graphicLibType != GraphicLib::NONE)
    {
        return false;
    }

    if (arg == "sdl2")
    {
        m_graphicLibType = GraphicLib::SDL2;
    }
    else if (arg == "raylib")
    {
        m_graphicLibType = GraphicLib::RAYLIB;
    }
    return true;
}

void App::Init()
{
    balls = std::vector<Ball*>();

    if (m_graphicLibType == GraphicLib::SDL2)
    {
        m_window = new WindowSDL();
        m_sprite = new SpriteSDL();
    }
    else if (m_graphicLibType == GraphicLib::RAYLIB) 
    {
        m_window = new WindowRaylib();
        m_sprite = new SpriteRaylib();
    }
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
