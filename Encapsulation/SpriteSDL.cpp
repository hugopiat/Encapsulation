#if _SDL
#include "SpriteSDL.h"
#include "SDL2/SDL_image.h"

SpriteSDL::SpriteSDL() :
    ASprite(),
    texture(nullptr),
    renderer(nullptr),
    destRect({ 0, 0, 0, 0 })
{
}

void SpriteSDL::Draw()
{
    destRect = { m_pos.m_x, m_pos.m_y, m_size.m_x, m_size.m_y };
	SDL_RenderCopy(renderer, texture, nullptr, &destRect);
	std::cout << "Draw sprite raylib !" << "\n";
}

void SpriteSDL::Update()
{
	std::cout << "Update sprite raylib !" << "\n";
}

void SpriteSDL::LoadImage(const std::string& filename)
{
    std::cout << "Load sprite SDL!" << "\n";

    texture = IMG_LoadTexture(renderer, filename.c_str());

    if (texture == nullptr) {
        std::cerr << "Erreur lors du chargement de l'image : " << IMG_GetError() << "\n";
        return;
    }

    SDL_QueryTexture(texture, NULL, NULL, &m_size.m_x, &m_size.m_y);
}

#endif