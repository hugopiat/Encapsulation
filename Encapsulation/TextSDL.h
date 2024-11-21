#pragma once
#include "AText.h"
typedef struct _TTF_Font TTF_Font;
class SDL_Color;
class SDL_Surface;
class SDL_Texture;
class WindowSDL;



class TextSDL : public AText
{

public:
	// Hérité via AText
	virtual void OnInit() override;
	virtual void Draw() override;
private:
	WindowSDL* m_windowCasted;
	TTF_Font* m_font;
	SDL_Color* m_color;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
};

