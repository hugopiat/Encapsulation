#pragma once
#include "Vector2.h"
#include "iostream"

class AWindow;

class ASprite
{
protected :

	Maths::Vector2 m_pos;
	Maths::Vector2 m_size;

	virtual void Load(const std::string& filename) = 0;

public :

	ASprite();
	virtual ~ASprite();

	virtual void Init(AWindow* window, const std::string& filename, int width = 50, int height = 50, int x = 0, int y = 0) = 0;
	virtual void Draw() = 0;

	virtual void SetPositionSprite(const Maths::Vector2& vect2D) = 0;
	virtual void SetSizeSprite(const Maths::Vector2& size2D) = 0;
};

