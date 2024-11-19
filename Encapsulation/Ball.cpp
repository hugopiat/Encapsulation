#include "Ball.h"

#include "ASprite.h"
#include "SpriteSDL.h"

Ball::Ball() : 
    m_pos(0,0),
    m_direction(0,0), 
    m_sprite(nullptr)
{

}

void Ball::Init(Maths::Vector2 pos, Maths::Vector2 speed, ASprite* sprite)
{
    m_pos.CopyVector2(pos);
    m_direction.CopyVector2(speed);
    m_sprite = sprite;
}

void Ball::SetSpeed(float speed)
{
    m_speed = speed;
}

void Ball::Update(float deltaTime, int windowWidth, int windowHeight)
{
    // Init new value
    int newX = m_pos.GetX() + (m_direction.GetX() * deltaTime * m_speed);
    int newY = m_pos.GetY() + (m_direction.GetY() * deltaTime * m_speed);

    // Check X bounds
    if (newX <= 0)
    {
        m_direction.SetX(ABS(m_direction.GetX()));
    }
    else if (newX >= windowWidth)
    {
        m_direction.SetX(-ABS(m_direction.GetX()));
    }

    // Check Y bounds
    if (newY <= 0)
    {
        m_direction.SetY(ABS(m_direction.GetY()));
    }
    else if (newY >= windowHeight)
    {
        m_direction.SetY(-ABS(m_direction.GetY()));
    }

    //Set X, Y new position
    m_pos.SetX(newX);
    m_pos.SetY(newY);
}

void Ball::Draw()
{
    m_sprite->SetPositionSprite(m_pos);
    m_sprite->Draw();
}

int Ball::ABS(int value)
{
    if (value >= 0) {
        return value;
    }
    else {
        return -value;
    }
}
