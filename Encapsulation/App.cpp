#include <sstream>
#include <iomanip>
#include "App.h"
#include "AWindow.h"
#include "AInputSystem.h"
#include "Timer.h"
#include "ASprite.h"
#include "Ball.h"
#include "Brick.h"
#include "Player.h"
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
    bricks = std::vector<Brick*>();

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

    SpawnBrick(5);
    SpawnPlayer();
    //SpawnBalls(50);
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
    InputUpdate();
    m_player->Update(deltaTime, m_window->m_width);
    for (int i = 0; i < balls.size(); i++) 
    {
        balls[i]->Update(deltaTime);
    }

    m_managerCollider->CheckAllCollisions();
    DeleteBricks();

    std::ostringstream oss;
    int fps = (1.f / Timer::GetDeltaTime());
    m_text->SetText(std::to_string(fps));
}

void App::SpawnPlayer()
{
    int brickSizeW = 125;
    int brickSizeH = 20;

    m_player = new Player();
    m_player->Init(Maths::Vector2(m_window->m_width / 2, m_window->m_height - brickSizeH), brickSizeW, brickSizeH, m_sprite);
    m_managerCollider->AddCollider(m_player->GetShape()->GetCollider());

    SpawnBallsNearPlayer(1);
}

void App::SpawnBallsNearPlayer(int count)
{
    int ballSize = 25;

    Ball* ball = new Ball();
    int x = m_player->GetShape()->GetPosition().GetX();
    int y = m_player->GetShape()->GetPosition().GetY() - ballSize * 1.5f;
    ball->Init(Maths::Vector2(x, y), Maths::Vector2(0, 0), m_sprite, ballSize);
    m_managerCollider->AddCollider(ball->GetCollider());
    ball->SetSpeed(500);

    balls.push_back(ball);
}

void App::SpawnBalls(int count)
{
    int ballSize = 25;

    std::srand(static_cast<unsigned>(std::time(0)));
    for (int i = 0; i < count; ++i)
    {
        float posX = (std::rand() % (m_window->m_width - (ballSize * 4))) + (ballSize * 2);
        float posY = (std::rand() % (m_window->m_height - (ballSize * 4))) + (ballSize * 2);

        float directionX = (std::rand() % 1000) - 500;
        float directionY = (std::rand() % 1000) - 500;

        Ball* ball = new Ball();
        ball->Init(Maths::Vector2(posX, posY), Maths::Vector2(directionX, directionY), m_sprite, ballSize);
        //ball->Init(Maths::Vector2(m_window->m_width / 2, m_window->m_height / 2), Maths::Vector2(directionX, directionY), m_sprite, ballSize);
        m_managerCollider->AddCollider(ball->GetCollider());
        ball->SetSpeed(250.0f);

        balls.push_back(ball);
    }
}

void App::SpawnBrick(int count)
{
    int brickSizeW = 100;
    int brickSizeH = 30;
    int nbBlock = m_window->m_width / brickSizeW; 
    float offsetX = (float)(m_window->m_width % brickSizeW) / nbBlock;

    for (size_t i = 0; i < count; i++)
    {
        bool endLine = false;
        int it = 0;

        while (!endLine)
        {
            float posX = (brickSizeW * it) + (brickSizeW / 2) + (offsetX * it);
            float posY = (brickSizeH * i) + (brickSizeH / 2) + (offsetX * i);

            if (posX + (brickSizeW / 2) > m_window->m_width)
            {
                break;
            }

            Brick* brick = new Brick();
            brick->Init(Maths::Vector2(posX, posY), m_sprite, brickSizeW, brickSizeH);
            m_managerCollider->AddCollider(brick->GetCollider());

            bricks.push_back(brick);
            it++;
        }
    }    
}

void App::InputUpdate()
{
    m_player->StopMoving();
    // Space Bar
    if (!m_player->m_isStarted && Encapsulation::AInputSystem::IsInputKeyDown(32))
    {
        balls[balls.size() - 1]->GetCollider()->SetDirection(Maths::Vector2(0, -1.0f));
        m_player->m_isStarted = true;
    }

    // Flèche Gauche
    if (Encapsulation::AInputSystem::IsInputKeyDown(113)) 
    {
        m_player->MoveToLeft();
        if (!m_player->m_isStarted)
        {
            int x = m_player->GetShape()->GetPosition().GetX();
            int y = balls[balls.size() - 1]->GetCollider()->GetPosition().GetY();
            balls[balls.size() - 1]->SetPosition(Maths::Vector2(x,y));
        }
    }

    // Flèche Droite
    if (Encapsulation::AInputSystem::IsInputKeyDown(100))
    {
        m_player->MoveToRight();
        if (!m_player->m_isStarted)
        {
            int x = m_player->GetShape()->GetPosition().GetX();
            int y = balls[balls.size() - 1]->GetCollider()->GetPosition().GetY();
            balls[balls.size() - 1]->SetPosition(Maths::Vector2(x, y));
        }
    }
}

void App::DeleteBalls() 
{
    // Lib�ration de la m�moire
    for (int i = 0; i < balls.size(); i++) 
    {
        delete balls[i];
    }
    delete m_window;
    delete m_sprite;
}

void App::DeleteBricks()
{
    for (auto it = bricks.begin(); it != bricks.end(); ) 
    {
        Brick* brick = *it;

        if (brick != nullptr && brick->m_isDie)
        {
            m_managerCollider->RemoveCollider(brick->GetCollider());
            brick->Destroy();
            it = bricks.erase(it);
            delete brick;
        }
        else 
        {
            ++it; 
        }
    }
}
