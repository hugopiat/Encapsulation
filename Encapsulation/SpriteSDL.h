#pragma once
#include "ASprite.h"

class WindowSDL;
class AWindow;
class SDL_Rect;
class SDL_Texture;

class SpriteSDL : public ASprite
{
private:
	WindowSDL* m_windowSDL;

	SDL_Rect* m_destRect;
	SDL_Texture* m_texture;

public:

	SpriteSDL();

	virtual void Init(AWindow* window, int x, int y, int width, int height) override;
	virtual void Draw() override;
	virtual void Update() override;
	virtual void Load(const std::string& filename) override;
};

