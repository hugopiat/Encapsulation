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
	UnloadTexture(m_texture);
}

void SpriteRaylib::Init(AWindow* window, const std::string& filename, int width, int height, int x, int y)
{
	//m_windowRAYLIB = dynamic_cast<WindowRAYLIB*>(window);
	m_pos.SetX(x);
	m_pos.SetY(y);
	m_size.SetX(width);
	m_size.SetY(height);
	Load(filename);
}

void SpriteRaylib::Draw()
{
	Vector2 pos = Vector2();
	pos.x = m_pos.GetX();
	pos.y = m_pos.GetY();
	//DrawTexture(m_texture, m_pos.GetX(), m_pos.GetY(), WHITE);
	DrawTextureEx(m_texture, pos, 0, 1, WHITE);
}

void SpriteRaylib::Update()
{
}

void SpriteRaylib::Load(const std::string& filename)
{
	std::cout << "Load sprite raylib !" << "\n";
	m_texture = LoadTexture(filename.c_str());
	m_texture.width = m_size.GetX();
	m_texture.height = m_size.GetY();
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
