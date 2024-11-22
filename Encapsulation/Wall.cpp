#include "Wall.h"

#include "BoxCollider.h"
#include "ASprite.h"

Wall::Wall(ASprite* sprite) :
    m_box(nullptr)
{
    m_sprite = sprite;
}

void Wall::CreateWall(int x, int y, int width, int height)
{
    m_box = new BoxCollider(Maths::Vector2(x, y), width, height);
    m_box->m_collisionType = CollisionType::Wall;
}

void Wall::Draw()
{
    m_sprite->Draw();
}

BoxCollider* Wall::GetCollider()
{
    return m_box;
}


