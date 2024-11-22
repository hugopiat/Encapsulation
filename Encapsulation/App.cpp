#include <sstream>
#include <iomanip>
#include "App.h"
#include "AWindow.h"
#include "AInputSystem.h"
#include "Timer.h"
#include "ASprite.h"
#include "Wall.h"
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
#if _SDL

#elif _RAYLIB

#endif
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
    m_balls = std::vector<Ball*>();    
    m_bricks = std::vector<Brick*>();
    m_walls = std::vector<Wall*>();

    Encapsulation::AInputSystem::Init();
    if (App::m_graphicLibType == GraphicLib::SDL2)
    {
        m_window = new WindowSDL();
        m_spriteBall = new SpriteSDL();
        m_spriteWall = new SpriteSDL();
        m_inputSystemInstance = new InputSystemSDL();
        m_inputLeft = 113;
        m_inputRight = 100;
    }
    else if (App::m_graphicLibType == GraphicLib::RAYLIB) 
    {
        m_window = new WindowRaylib();
        m_spriteBall = new SpriteRaylib();
        m_spriteWall = new SpriteRaylib();
        m_inputSystemInstance = new InputSystemRaylib();
        m_inputLeft = 65;
        m_inputRight = 68;
    }

    m_timer = new Timer();
    m_managerCollider = new ColliderManager();


    if (m_window == nullptr || m_timer == nullptr || m_spriteBall == nullptr || m_spriteBall == m_spriteWall)
    {
        return;
    }

    m_window->Init();
    m_spriteBall->Init(m_window, m_filenameBall);
    m_spriteWall->Init(m_window, m_filenameWall);
    m_walls = m_managerCollider->InitWalls(m_window, m_spriteWall);

    m_text = TextManager::GetInstance()->InstantiateText();
    m_text->Init(m_window, "FPS", 1130, 30, 100);

    SpawnBrick(10);
    SpawnPlayer();
    //SpawnBalls(5);
}

void App::Draw()
{
    m_window->Clear();
    //m_managerCollider->DrawDebugAll(m_window);
    
    for (int i = 0; i < m_balls.size(); i++) 
    {
        m_balls[i]->Draw();
    }
    for (int i = 0; i < m_bricks.size(); i++)
    {
        m_bricks[i]->Draw();
    }
    for (int i = 0; i < m_walls.size(); i++)
    {
        m_walls[i]->Draw();
    }
    m_player->Draw();
    m_text->Draw();
    m_window->Draw();    
}

void App::Update(float deltaTime)
{
    if (m_player) 
    {
        InputUpdate();
        m_player->Update(deltaTime, m_window->m_width);
    }
    for (int i = 0; i < m_balls.size(); i++) 
    {
        m_balls[i]->Update(deltaTime);
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
    m_player->Init(Maths::Vector2(m_window->m_width / 2, m_window->m_height - brickSizeH), brickSizeW, brickSizeH, m_spriteWall);
    m_managerCollider->AddCollider(m_player->GetShape()->GetCollider());

    SpawnBallsNearPlayer(1);
}

void App::SpawnBallsNearPlayer(int count)
{
    int ballSize = 25;

    Ball* ball = new Ball();
    int x = m_player->GetShape()->GetPosition().GetX();
    int y = m_player->GetShape()->GetPosition().GetY() - ballSize * 1.5f;
    ball->Init(Maths::Vector2(x, y), Maths::Vector2(0, 0), m_spriteBall, ballSize);
    m_managerCollider->AddCollider(ball->GetCollider());
    ball->SetSpeed(500);

    m_balls.push_back(ball);
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
        ball->Init(Maths::Vector2(posX, posY), Maths::Vector2(directionX, directionY), m_spriteBall, ballSize);
        //ball->Init(Maths::Vector2(m_window->m_width / 2, m_window->m_height / 2), Maths::Vector2(directionX, directionY), m_sprite, ballSize);
        m_managerCollider->AddCollider(ball->GetCollider());
        ball->SetSpeed(250.0f);

        m_balls.push_back(ball);
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
            brick->Init(Maths::Vector2(posX, posY), m_spriteWall, brickSizeW, brickSizeH);
            m_managerCollider->AddCollider(brick->GetCollider());

            m_bricks.push_back(brick);
            it++;
        }
    }    
}

void App::InputUpdate()
{
    m_player->StopMoving();

    Maths::Vector2 directionBall = Maths::Vector2(0, -1.0f);

    // Flèche Gauche
    if (Encapsulation::AInputSystem::IsInputKeyDown(m_inputLeft))
    {
        m_player->MoveToLeft();
        directionBall += Maths::Vector2(-0.5f, 0.0f);
        if (!m_balls[m_balls.size() - 1]->m_isStarted)
        {
            int x = m_player->GetShape()->GetPosition().GetX();
            int y = m_balls[m_balls.size() - 1]->GetCollider()->GetPosition().GetY();
            m_balls[m_balls.size() - 1]->SetPosition(Maths::Vector2(x,y));
        }
    }

    // Flèche Droite
    if (Encapsulation::AInputSystem::IsInputKeyDown(m_inputRight))
    {
        m_player->MoveToRight();
        directionBall += Maths::Vector2(0.5f, 0.0f);
        if (!m_balls[m_balls.size() - 1]->m_isStarted)
        {
            int x = m_player->GetShape()->GetPosition().GetX();
            int y = m_balls[m_balls.size() - 1]->GetCollider()->GetPosition().GetY();
            m_balls[m_balls.size() - 1]->SetPosition(Maths::Vector2(x, y));
        }
    }

    m_currentCooldown += Timer::GetDeltaTime();
    // Space Bar
    if (!m_balls[m_balls.size() - 1]->m_isStarted && Encapsulation::AInputSystem::IsInputKeyDown(32) && m_currentCooldown >= m_cooldownSpawn)
    {
        m_balls[m_balls.size() - 1]->GetCollider()->SetDirection(directionBall);
        m_balls[m_balls.size() - 1]->m_isStarted = true;
        SpawnBallsNearPlayer(1);
        m_currentCooldown = 0.0f;
    }
}

void App::DeleteBalls() 
{
    // Lib�ration de la m�moire
    for (int i = 0; i < m_balls.size(); i++) 
    {
        delete m_balls[i];
    }
    delete m_window;
    delete m_spriteBall;
}

void App::DeleteBricks()
{
    for (auto it = m_bricks.begin(); it != m_bricks.end(); ) 
    {
        Brick* brick = *it;

        if (brick != nullptr && brick->m_isDie)
        {
            m_managerCollider->RemoveCollider(brick->GetCollider());
            brick->Destroy();
            it = m_bricks.erase(it);
            delete brick;
        }
        else 
        {
            ++it; 
        }
    }
}
