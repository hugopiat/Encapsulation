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
    std::cout << "[SDL] On Create Sprite !" << "\n";
}

void SpriteSDL::Init(AWindow* window, const std::string& filename, int width, int height, int x, int y)
{
    m_windowSDL = dynamic_cast<WindowSDL*>(window);
    m_destRect = new SDL_Rect();

    SetPositionSprite(Maths::Vector2(x, y));
    SetSizeSprite(Maths::Vector2(width, height));

    Load(filename);

    std::cout << "[SDL] On Init Sprite !" << "\n";
}

void SpriteSDL::Draw()
{
    //std::cout << "Draw sprite SDL !" << "\n";

    if (m_texture)
    {
        UpdateDestRect();

        SDL_RenderCopy(m_windowSDL->GetRenderer(), m_texture, nullptr, m_destRect);
    }
}

void SpriteSDL::Update()
{
	std::cout << "[SDL] On Update Sprite !" << "\n";
}

void SpriteSDL::UpdateDestRect()
{
    m_destRect->x = m_pos.GetX();
    m_destRect->y = m_pos.GetY();
    m_destRect->w = m_size.GetX();
    m_destRect->h = m_size.GetY();
}

void SpriteSDL::Load(const std::string& filename)
{
    if (m_texture != nullptr)
    {
        SDL_DestroyTexture(m_texture);
        m_texture = nullptr;
    }

    SDL_Surface* tempSurface = IMG_Load(filename.c_str());
    if (!tempSurface)
    {
        std::cerr << "[SDL - ERROR] Image load issue : " << SDL_GetError() << std::endl;
        return;
    }

    m_texture = SDL_CreateTextureFromSurface(m_windowSDL->GetRenderer(), tempSurface);
    SDL_FreeSurface(tempSurface); 

    if (!m_texture)
    {
        std::cerr << "[SDL - ERROR] Texture load issue : " << SDL_GetError() << std::endl;
        return;
    }

    SDL_QueryTexture(m_texture, nullptr, nullptr, &m_destRect->w, &m_destRect->h);

    std::cout << "[SDL] On Load Sprite !" << "\n";
}

void SpriteSDL::SetPositionSprite(Maths::Vector2 vect2D)
{
    m_pos.SetX(vect2D.GetX() - (m_size.GetX() / 2));
    m_pos.SetY(vect2D.GetY() - (m_size.GetY() / 2));
    UpdateDestRect();
}

void SpriteSDL::SetSizeSprite(Maths::Vector2 size2D)
{
    m_size.SetX(size2D.GetX());
    m_size.SetY(size2D.GetY());
    UpdateDestRect();
}
