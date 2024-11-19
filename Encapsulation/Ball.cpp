#include "Ball.h"

#include "ASprite.h"
#include "SpriteSDL.h"

Ball::Ball() : 
    m_pos(0,0),
    m_speed(0,0), 
    m_sprite(nullptr)
{

}

void Ball::Init(Maths::Vector2 pos, Maths::Vector2 speed, ASprite* sprite)
{
    m_pos.CopyVector2(pos);
    m_speed.CopyVector2(speed);
    m_sprite = sprite;
}

void Ball::Update(float deltaTime, int windowWidth, int windowHeight)
{
    // Init new value
    int newX = m_pos.GetX() + (m_speed.GetX() * deltaTime);
    int newY = m_pos.GetY() + (m_speed.GetY() * deltaTime);

    // Check X bounds
    if (newX <= 0)
    {
        m_speed.SetX(ABS(m_speed.GetX()));
    }
    else if (newX >= windowWidth)
    {
        m_speed.SetX(-ABS(m_speed.GetX()));
    }

    // Check Y bounds
    if (newY <= 0)
    {
        m_speed.SetY(ABS(m_speed.GetY()));
    }
    else if (newY >= windowHeight)
    {
        m_speed.SetY(-ABS(m_speed.GetY()));
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
