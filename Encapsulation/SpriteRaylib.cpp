#include "SpriteRaylib.h"
//#include "WindowRAYLIB.h"
#include "AWindow.h"

SpriteRaylib::SpriteRaylib() :
	ASprite(),
	m_texture(nullptr)
{

}

SpriteRaylib::~SpriteRaylib()
{
	std::cout << "Draw sprite raylib !" << "\n";
	UnloadTexture(*m_texture);
}

void SpriteRaylib::Init(AWindow* window, const std::string& filename, int width, int height, int x, int y)
{
	//m_windowRAYLIB = dynamic_cast<WindowRAYLIB*>(window);

	Load(filename);

	SetPositionSprite(Maths::Vector2(x, y));
	SetSizeSprite(Maths::Vector2(width, height));
}

void SpriteRaylib::Draw()
{
	Vector2 pos = Vector2();
	pos.x = m_pos.GetX();
	pos.y = m_pos.GetY();
	//DrawTexture(*m_texture, m_pos.GetX(), m_pos.GetY(), WHITE);
	DrawTextureEx(*m_texture, pos, 0, 1, WHITE);
}

void SpriteRaylib::Load(const std::string& filename)
{
	std::cout << "Load sprite raylib !" << "\n";
	m_texture = new Texture2D(LoadTexture(filename.c_str()));
}

void SpriteRaylib::SetPositionSprite(const Maths::Vector2& vect2D)
{
    m_pos.SetX(vect2D.GetX() - (m_size.GetX() / 2));
    m_pos.SetY(vect2D.GetY() - (m_size.GetY() / 2));
}

void SpriteRaylib::SetSizeSprite(const Maths::Vector2& size2D)
{
	m_size.SetX(size2D.GetX());
	m_size.SetY(size2D.GetY());

	if (m_texture)
	{
		m_texture->width = m_size.GetX();
		m_texture->height = m_size.GetY();
	}
}

