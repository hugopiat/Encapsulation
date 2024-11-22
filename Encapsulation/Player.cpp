#include "Player.h"

#include "Brick.h"
#include "Collider.h"

Player::Player():
    m_shape(nullptr),
    m_speed(0.0f),
    m_direction(0.0f),
    m_width(0)
{
}

void Player::Init(Maths::Vector2 pos, int width, int height, ASprite* sprite)
{
    m_shape = new Brick();
    m_shape->Init(pos, sprite, width, height);
    m_shape->m_enabledLife = false;

    m_speed = 1000.0f;
    m_width = width;
}

void Player::Update(float deltaTime, int widthMax)
{
    float moveAmount = m_speed * deltaTime;
    if (m_direction != 0)
    {
        MoveHorizontally(moveAmount, widthMax);
    }
}

void Player::MoveHorizontally(float moveAmount, int widthMax)
{
    float newPosX = m_shape->GetPosition().GetX() + m_direction * moveAmount;

    if (newPosX < 0)
    {
        newPosX = 0; 
    }
    else if (newPosX + (m_width / 2) > widthMax)
    {
        newPosX = widthMax - (m_width / 2);
    }

    m_shape->SetPosition(Maths::Vector2(newPosX, m_shape->GetPosition().GetY()));
}

void Player::MoveToLeft()
{
    m_direction = -1.0f;
}

void Player::MoveToRight()
{
    m_direction = 1.0f;
}

void Player::StopMoving()
{
    m_direction = 0.0f; 
}

Brick* Player::GetShape()
{
    return m_shape;
}
