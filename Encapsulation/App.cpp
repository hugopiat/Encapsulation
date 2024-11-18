#include "App.h"

#if _SDL
#include "WindowSDL.h"
#endif // _SDL


void App::Run()
{
#if _SDL
	m_window = new WindowSDL();
#endif // _SDL


	m_window->Init();
	while (m_window->IsOpen())
	{
		Update();
		m_window->Clear();
		m_window->Draw();
	}

}

void App::Update()
{
}
