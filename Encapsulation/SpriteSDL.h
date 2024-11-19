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

	void UpdateDestRect();
	virtual void Load(const std::string& filename) override;

public:

	SpriteSDL();

	virtual void Init(AWindow* window, const std::string& filename, int width = 0, int height = 0, int x = 0, int y = 0) override;
	virtual void Draw() override;
	virtual void Update() override;

	virtual void SetPositionSprite(Maths::Vector2 vect2D) override;
	virtual void SetSizeSprite(Maths::Vector2 size2D) override;
};

