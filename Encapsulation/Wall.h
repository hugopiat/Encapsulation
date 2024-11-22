#pragma once
#include <iostream>
#include "Vector2.h"

class ASprite;
class BoxCollider;

class Wall
{
private :
	const std::string m_filenameWall = "Wall.png";

	BoxCollider* m_box;
	ASprite* m_sprite;
	Maths::Vector2 m_pos;
	Maths::Vector2 m_size;

public : 

	Wall();

	void CreateWall(ASprite* sprite, const Maths::Vector2 pos, int width, int height);
	void Draw();

	BoxCollider* GetCollider();
};

