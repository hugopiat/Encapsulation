#include "TextManager.h"
#include "App.h"
#include "TextRaylib.h"
#include "TextSDL.h"

TextManager* TextManager::s_instance = nullptr;

AText* TextManager::InstantiateText()
{
	if (App::GetGraphicLibType() == GraphicLib::RAYLIB)
	{
		return new TextRaylib();
	}
	else if (App::GetGraphicLibType() == GraphicLib::SDL2) 
	{
		return new TextSDL();
	}
	return nullptr;
}

TextManager* TextManager::GetInstance()
{
	if (s_instance == nullptr)
	{
		s_instance = new TextManager();
	}
	return s_instance;
}
