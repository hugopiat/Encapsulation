#pragma once
#include "Vector2.h"

class Brick;
class ASprite;

class Player
{
private : 
	Brick* m_shape;
	float m_speed;
	float m_direction;
	int m_width;

public :

	bool m_isStarted;

	Player();
	void Init(Maths::Vector2 pos, int width, int height, ASprite* sprite);
	void Update(float deltaTime, int widthMax);

	void MoveHorizontally(float moveAmount, int widthMax);
	void MoveToLeft();
	void MoveToRight();
	void StopMoving();

	Brick* GetShape();
};

