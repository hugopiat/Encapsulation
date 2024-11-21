#pragma once
#include "Vector2.h"

class Brick;
class ASprite;

class Player
{
private : 
	Brick* m_shape;
	float m_speed;

public :

	Player();
	void Init(Maths::Vector2 pos, int width, int height, ASprite* sprite);

	void MoveToLeft();
	void MoveToRight(int widthMax);

	Brick* GetShape();
};

