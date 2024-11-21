#include "Player.h"

#include "Brick.h"

Player::Player():
    m_shape(nullptr),
    m_speed(0.0f)
{
}

void Player::Init(Maths::Vector2 pos, int width, int height, ASprite* sprite)
{
    m_shape = new Brick();
    m_shape->Init(pos, sprite, width, height);
    m_shape->m_enabledLife = false;
    m_speed = 10.0f;
}

void Player::MoveToLeft()
{
    if (m_shape->GetPosition().GetX() - m_speed > 0) 
    {
        Maths::Vector2 newPos = Maths::Vector2(m_shape->GetPosition().GetX() - m_speed, m_shape->GetPosition().GetY());
        m_shape->SetPosition(newPos);
    }
}

void Player::MoveToRight(int widthMax)
{
    if (m_shape->GetPosition().GetX() + m_speed < widthMax)
    {
        Maths::Vector2 newPos = Maths::Vector2(m_shape->GetPosition().GetX() + m_speed, m_shape->GetPosition().GetY());
        m_shape->SetPosition(newPos);
    }
}

Brick* Player::GetShape()
{
    return m_shape;
}
