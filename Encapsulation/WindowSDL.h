#if _SDL
#pragma once
#include "AWindow.h"

class SDL_Surface;
class SDL_Window;

class WindowSDL : public AWindow
{
private:
	SDL_Surface* m_winSurface;
	SDL_Window* m_window;
	bool m_isSdlInit;

	bool InitLib();
	bool CreateWindow();
	bool GetSurface();

public:
	WindowSDL();
	// Hérité via AWindow
	void Init() override;
	void Draw() override;
	void Clear() override;
	bool IsOpen() override;

	// Hérité via AWindow
};
#endif // _SDL

