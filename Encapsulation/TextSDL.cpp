#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TextSDL.h"
#include "WindowSDL.h"

void TextSDL::OnInit()
{
	if (!(m_windowCasted = dynamic_cast<WindowSDL*>(m_window)))
	{
		return;
	}
	m_font = TTF_OpenFont("Fonts/ncl-maxipower/NCLMaxipower-Demo.ttf", 256);
	if (m_font == nullptr)
	{
		std::cout << "Fail to Load Texture" << std::endl;
	}
	
	m_color = new SDL_Color({ 255, 255, 255 });

	std::cout << "On Init SDL Text" << std::endl;
}

void TextSDL::Draw()
{
	m_surface = TTF_RenderText_Solid(m_font, m_text.c_str(), *m_color);
	m_texture = SDL_CreateTextureFromSurface(m_windowCasted->GetRenderer(), m_surface);

	SDL_Rect Message_rect;
	Message_rect.x = m_pos.GetX();
	Message_rect.y = m_pos.GetY();
	Message_rect.w = m_fontSize * 1.2f;
	Message_rect.h = m_fontSize;

	SDL_RenderCopy(m_windowCasted->GetRenderer(), m_texture, NULL, &Message_rect);

	SDL_FreeSurface(m_surface);
	SDL_DestroyTexture(m_texture);
}
