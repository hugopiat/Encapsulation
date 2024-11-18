#pragma once
#include "Vector2.h"
#include "iostream"

class ASprite
{
public :

	Vector2 m_pos;
	Vector2 m_size;

	ASprite();
	virtual ~ASprite();

	virtual void SetPositionSprite(Vector2 vect2D);
	virtual void SetSizeSprite(Vector2 size2D);

	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void LoadImage(const std::string& filename) = 0;
};

