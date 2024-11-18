#pragma once
#include "ASprite.h"
#include "SDL2/SDL.h"

class SpriteSDL : public ASprite
{
private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	SDL_Rect destRect;

public:
	SpriteSDL();

	virtual void Draw() override;
	virtual void Update() override;
	virtual void LoadImage(const std::string& filename) override;
};

