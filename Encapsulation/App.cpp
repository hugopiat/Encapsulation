#include <sstream>
#include <iomanip>
#include "App.h"
#include "AWindow.h"
#include "AInputSystem.h"
#include "Timer.h"
#include "ASprite.h"
#include "Ball.h"
#include "ColliderManager.h"
#include "BoxCollider.h"
#include "TextManager.h"

#include "WindowSDL.h"
#include "SpriteSDL.h"
#include "InputSystemSDL.h"

#include "WindowRaylib.h"
#include "SpriteRaylib.h"
#include "TextRaylib.h"
#include "InputSystemRaylib.h"
using namespace Encapsulation;

GraphicLib App::m_graphicLibType = GraphicLib::NONE;

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
            m_inputSystemInstance->PoolEvent();
            float deltaTime = Timer::GetDeltaTime();
            Update(deltaTime);
            Draw();      
        }
    }

    m_window->Close();
    DeleteBalls();
}

GraphicLib App::GetGraphicLibType()
{
    return App::m_graphicLibType;
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
    
    Encapsulation::AInputSystem::Init();
    if (App::m_graphicLibType == GraphicLib::SDL2)
    {
        m_window = new WindowSDL();
        m_sprite = new SpriteSDL();
        m_inputSystemInstance = new InputSystemSDL();
    }
    else if (App::m_graphicLibType == GraphicLib::RAYLIB) 
    {
        m_window = new WindowRaylib();
        m_sprite = new SpriteRaylib();
        m_inputSystemInstance = new InputSystemRaylib();
    }

    m_timer = new Timer();
    m_managerCollider = new ColliderManager();


    if (m_window == nullptr || m_timer == nullptr || m_sprite == nullptr)
    {
        return;
    }

    m_window->Init();
    m_managerCollider->InitWalls(m_window->m_width, m_window->m_height);
    m_sprite->Init(m_window, filename);
    m_text = TextManager::GetInstance()->InstantiateText();
    m_text->Init(m_window, "FPS", 1130, 30, 100);
    SpawnBalls(100);
}

void App::Draw()
{
    m_window->Clear();
    m_managerCollider->DrawDebugAll(m_window);
    
    for (int i = 0; i < balls.size(); i++) 
    {
        balls[i]->Draw();
    }
    m_text->Draw();
    m_window->Draw();    
}

void App::Update(float deltaTime)
{
    for (int i = 0; i < balls.size(); i++) {
        balls[i]->Update(deltaTime, m_window->m_width, m_window->m_height);
    }
    std::ostringstream oss;
    int fps = (1.f / Timer::GetDeltaTime());
    m_text->SetText(std::to_string(fps));
    m_managerCollider->CheckAllCollisions();
    //m_managerCollider->CheckAllCollisionsWithBounds();
}

void App::SpawnBalls(int count)
{
    int ballSize = 25;

    std::srand(static_cast<unsigned>(std::time(0)));
    for (int i = 0; i < count; ++i) {

        float posX = (std::rand() % (m_window->m_width - (ballSize * 4))) + (ballSize * 2);
        float posY = (std::rand() % (m_window->m_height - (ballSize * 4))) + (ballSize * 2);

        float directionX = (std::rand() % 10) - 5;
        float directionY = (std::rand() % 10) - 5;

        Ball* ball = new Ball();
        ball->Init(Maths::Vector2(posX, posY), Maths::Vector2(directionX, directionY), m_sprite, ballSize);
        //ball->Init(Maths::Vector2(m_window->m_width / 2, m_window->m_height / 2), Maths::Vector2(directionX, directionY), m_sprite, ballSize);
        m_managerCollider->AddCollider(ball->GetCollider());
        ball->SetSpeed(250.0f);

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
