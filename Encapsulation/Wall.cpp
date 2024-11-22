#include "Wall.h"

#include "BoxCollider.h"
#include "ASprite.h"

Wall::Wall() :
    m_box(nullptr),
    m_sprite(nullptr)
{
}

void Wall::CreateWall(ASprite* sprite, const Maths::Vector2 pos, int width, int height)
{
    m_sprite = sprite;
    m_pos = pos;
    m_size = Maths::Vector2(width, height);
    m_box = new BoxCollider(pos, width, height);
    m_box->m_collisionType = CollisionType::Wall;

    m_sprite->SetSizeSprite(m_size);
}

void Wall::Draw()
{
    m_sprite->SetSizeSprite(m_size);
    m_sprite->SetPositionSprite(m_pos);
    m_sprite->Draw();
}

BoxCollider* Wall::GetCollider()
{
    return m_box;
}


