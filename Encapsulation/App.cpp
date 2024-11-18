#include "App.h"
#include "AWindow.h"

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

    m_sprite->Init(m_window, 640, 360, 50, 50);
    m_sprite->Load("Basketball.png");

    while (m_window->IsOpen())
    {
        m_window->Clear();
        Update(); 
        m_sprite->Draw(); 
        m_window->Draw();

#if _SDL
        SDL_Delay(16);  // ~16 ms pour correspondre à environ 60 FPS
#elif _RAYLIB

#endif
    }

    m_window->Close();
}

void App::Update()
{
}
