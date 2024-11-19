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
	DrawTexture(texture, m_pos.GetPositionX(), m_pos.GetPositionY(), WHITE);
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

#endif
