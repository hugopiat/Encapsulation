#pragma once
#include <iostream>

class ASprite;
class BoxCollider;

class Wall
{
private :
	const std::string m_filenameWall = "Wall.png";

	BoxCollider* m_box;
	ASprite* m_sprite;

public : 

	Wall(ASprite* sprite);

	void CreateWall(int x, int y, int width, int height);
	void Draw();

	BoxCollider* GetCollider();
};

