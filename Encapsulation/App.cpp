#include "App.h"
#include "AWindow.h"
#include "Ball.h"

#if _SDL
#include "WindowSDL.h"
#include "SpriteSDL.h"
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

    m_sprite->Init(m_window, 0, 0, 50, 50);
    m_sprite->Load("Basketball.png");

    SpawnBalls(50);

    while (m_window->IsOpen())
    {
        Update(0.5f);
        Draw();      
    }

    m_window->Close();

    // Libération de la mémoire
    for (int i = 0; i < balls.size(); i++) {
        delete balls[i];
    }
    delete m_window;
    delete m_sprite;
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
        float x = std::rand() % 800;
        float y = std::rand() % 600;
        float speedX = (std::rand() % 100) - 50; // Vitesse entre -50 et 50
        float speedY = (std::rand() % 100) - 50;

        Ball* ball = new Ball();
        ball->Init(Maths::Vector2(x, y), Maths::Vector2(speedX, speedY), m_sprite);
        balls.push_back(ball);
    }
}
