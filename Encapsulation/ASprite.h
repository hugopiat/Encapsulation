#pragma once
#include "Vector2.h"
#include "iostream"

class AWindow;

class ASprite
{
public :

	Maths::Vector2 m_pos;
	Maths::Vector2 m_size;

	ASprite();
	virtual ~ASprite();

	virtual void SetPositionSprite(Maths::Vector2 vect2D);
	virtual void SetSizeSprite(Maths::Vector2 size2D);

	virtual void Init(AWindow* window, int x = 0, int y = 0, int width = 0, int height = 0) = 0;
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void Load(const std::string& filename) = 0;
};

