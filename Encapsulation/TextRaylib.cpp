#include "TextRaylib.h"
#include <raylib.h>

void TextRaylib::OnInit()
{
	m_font = LoadFontEx("Fonts/ncl-maxipower/NCLMaxipower-Demo.otf",256,0,250);
}

void TextRaylib::Draw()
{
	Vector2 pos;
	pos.x = m_pos.GetX();
	pos.y = m_pos.GetY();
	DrawTextEx(m_font, m_text.c_str(),pos, m_fontSize, 4, WHITE);
}
