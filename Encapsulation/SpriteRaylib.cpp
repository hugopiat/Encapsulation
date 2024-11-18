#if _RAYLIB
#include "SpriteRaylib.h"

SpriteRaylib::SpriteRaylib() :
	ASprite()
{

}

void SpriteRaylib::Draw()
{
	std::cout << "Draw sprite raylib !" << "\n";
}

void SpriteRaylib::Update()
{
	std::cout << "Update sprite raylib !" << "\n";
}

void SpriteRaylib::LoadImage()
{
	std::cout << "Load sprite raylib !" << "\n";
}

#endif
