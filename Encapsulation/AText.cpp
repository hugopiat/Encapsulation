#include "AText.h"

AText::AText() : 
	m_fontSize(0), m_pos(0,0), m_text()
{
}

void AText::Init(AWindow* window, std::string text, int posX, int posY, int fontSize)
{
	m_text = text;
	m_fontSize = fontSize;
	m_pos = Maths::Vector2(posX, posY);
	m_window = window;

	OnInit();
}

void AText::SetText(std::string text)
{
	m_text = text;
}
