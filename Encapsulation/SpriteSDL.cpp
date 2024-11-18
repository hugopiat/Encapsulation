#if _SDL
#include "SpriteSDL.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "WindowSDL.h"
#include "AWindow.h"

SpriteSDL::SpriteSDL() :
    ASprite(),
    m_windowSDL(nullptr),
    m_texture(nullptr),
    m_destRect(nullptr)
{

}

void SpriteSDL::Init(AWindow* window, int x, int y, int width, int height)
{
    m_windowSDL = dynamic_cast<WindowSDL*>(window);

    SetPositionSprite(Maths::Vector2(x, y));
    SetSizeSprite(Maths::Vector2(width, height));

    m_destRect = new SDL_Rect();
}

void SpriteSDL::Draw()
{
    std::cout << "Draw sprite SDL !" << "\n";

    if (m_texture)
    {
        m_destRect->x = m_pos.GetX();
        m_destRect->y = m_pos.GetY();
        m_destRect->w = m_size.GetX();
        m_destRect->h = m_size.GetY();

        SDL_RenderCopy(m_windowSDL->GetRenderer(), m_texture, nullptr, m_destRect);
    }
}

void SpriteSDL::Update()
{
	std::cout << "Update sprite SDL !" << "\n";
}

void SpriteSDL::Load(const std::string& filename)
{
    std::cout << "Load sprite SDL !" << "\n";

    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    SDL_Surface* tempSurface = IMG_Load(filename.c_str());
    if (!tempSurface)
    {
        std::cerr << "Erreur de chargement de l'image : " << SDL_GetError() << std::endl;
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(m_windowSDL->GetRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface); 

    if (!m_texture)
    {
        std::cerr << "Erreur de création de la texture : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect->w, &m_destRect->h);
}

#endif