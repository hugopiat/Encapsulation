#include "App.h"
#include "AWindow.h"
#include "ATimer.h"
#include "Ball.h"

#if _SDL
#include "WindowSDL.h"
#include "SpriteSDL.h"
#include "TimerSDL.h"
#include <SDL2/SDL_timer.h>
#endif // _SDL

#if _RAYLIB
#include "SpriteRaylib.h"
#endif // _SDL


void App::Run()
{
	m_window = nullptr;
	m_sprite = nullptr;

    balls = std::vector<Ball*>();

#if _SDL
    m_timer = new TimerSDL();
	m_window = new WindowSDL();
	m_sprite = new SpriteSDL();
#elif _RAYLIB

	m_sprite = new SpriteRaylib();

#endif

	if (m_window == nullptr)
	{
		return;
	}

    m_window->Init();
    m_sprite->Init(m_window, filename, 50, 50);

    SpawnBalls(50);

    while (m_window->IsOpen())
    {
        if (m_timer->UpdateTime())
        {
            Update(ATimer::GetDeltaTime());
            Draw();      
        }
    }

    m_window->Close();
    DeleteBalls();
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
        ball->SetSpeed(10.0f);
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
