#pragma once
#include "Vector2.h"
#include "iostream"

class ASprite
{
public :

	Vector2 m_pos;

	ASprite();
	virtual ~ASprite();
	virtual void Draw() = 0;
	virtual void Update() = 0;
	virtual void LoadImage() = 0;
};

