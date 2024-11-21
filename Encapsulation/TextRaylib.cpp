#include "TextRaylib.h"
#include <raylib.h>

void TextRaylib::OnInit()
{
	m_font = LoadFont("Fonts/ncl-maxipower/NCLMaxipower-Demo.otf");
}

void TextRaylib::Draw()
{
	DrawText(m_text.c_str(), m_pos.GetX(), m_pos.GetY(), m_fontSize, WHITE);
}
