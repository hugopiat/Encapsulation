#if _RAYLIB
#include "SpriteRaylib.h"
//#include "WindowRAYLIB.h"
#include "AWindow.h"

SpriteRaylib::SpriteRaylib() :
	ASprite()
{

}

SpriteRaylib::~SpriteRaylib()
{
	std::cout << "Draw sprite raylib !" << "\n";
	UnloadTexture(texture);
}

void SpriteRaylib::Init(AWindow* window, const std::string& filename, int width, int height, int x, int y)
{
	//m_windowRAYLIB = dynamic_cast<WindowRAYLIB*>(window);
	m_pos.SetX(x);
	m_pos.SetY(x);
	m_size.SetX(width);
	m_pos.SetY(height);
}

void SpriteRaylib::Draw()
{
	std::cout << "Draw sprite raylib !" << "\n";
	DrawTexture(texture, m_pos.GetX(), m_pos.GetY(), WHITE);
}

void SpriteRaylib::Update()
{
	std::cout << "Update sprite raylib !" << "\n";
}

void SpriteRaylib::Load(const std::string& filename)
{
	std::cout << "Load sprite raylib !" << "\n";
	texture = LoadTexture(filename.c_str());
}

void SpriteRaylib::SetPositionSprite(Maths::Vector2 vect2D)
{
	m_pos.SetX(vect2D.GetX() - (m_size.GetX() / 2));
	m_pos.SetY(vect2D.GetY() - (m_size.GetY() / 2));
}

void SpriteRaylib::SetSizeSprite(Maths::Vector2 size2D)
{
	m_size.SetX(size2D.GetX());
	m_size.SetY(size2D.GetY());
}

#endif
