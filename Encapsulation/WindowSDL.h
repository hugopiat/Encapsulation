#pragma once
#include "AWindow.h"

class SDL_Surface;
class SDL_Window;
class SDL_Renderer;

class WindowSDL : public AWindow
{
private:
	SDL_Surface* m_winSurface;
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isSdlInit;

	bool InitLib();
	bool InitRenderer();
	bool CreateWindow();
	bool GetSurface();

public:

	WindowSDL();
	// Hérité via AWindow
	void Init() override;
	void Draw() override;
	void Clear() override;
	bool IsOpen() override;
	bool Close() override;

	SDL_Renderer* GetRenderer();
};

