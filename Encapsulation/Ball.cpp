#include "Ball.h"

#include "ASprite.h"
#include "SpriteSDL.h"

Ball::Ball() : 
    m_pos(0,0),
    m_direction(0,0), 
    m_sprite(nullptr)
{

}

void Ball::Init(Maths::Vector2 pos, Maths::Vector2 direction, ASprite* sprite)
{
    m_pos = pos;
    m_direction = speed;
    m_sprite = sprite;
}

void Ball::SetSpeed(float speed)
{
    m_speed = speed;
}

Maths::Vector2 Ball::InitNextPos(float deltaTime)
{
    // Init next pos
    Maths::Vector2 nextPos = Maths::Vector2(
        m_pos.GetX() + (m_direction.GetX() * deltaTime * m_speed),
        m_pos.GetY() + (m_direction.GetY() * deltaTime * m_speed));

    return nextPos;
}

Maths::Vector2 Ball::GetNormalVector(int posX, int posY, int windowWidth, int windowHeight)
{
    Maths::Vector2 vecteurNormal = Maths::Vector2(0, 0);
    if (posX <= 0)
    {
        vecteurNormal += Maths::Vector2(1, 0);
    }
    else if (posX >= windowWidth)
    {
        vecteurNormal += Maths::Vector2(-1, 0);
    }

    if (posY <= 0)
    {
        vecteurNormal += Maths::Vector2(0, 1);
    }
    else if (posY >= windowHeight)
    {
        vecteurNormal += Maths::Vector2(0, -1);
    }

    return vecteurNormal;
}

void Ball::Update(float deltaTime, int windowWidth, int windowHeight)
{
    Maths::Vector2 nextPos = InitNextPos(deltaTime);

    // Calculate Scalar product by direction and normalVector
    Maths::Vector2 vecteurNormal = GetNormalVector(nextPos.GetX(), nextPos.GetY(), windowWidth, windowHeight);

    if (vecteurNormal != Maths::Vector2(0, 0)) 
    {
        int scalarProduct = (m_direction.GetX() * vecteurNormal.GetX()) + (m_direction.GetY() * vecteurNormal.GetY());

        // Init new direction
        Maths::Vector2 newDirection = Maths::Vector2(
            m_direction.GetX() - (2 * scalarProduct * vecteurNormal.GetX()),
            m_direction.GetY() - (2 * scalarProduct * vecteurNormal.GetY()));

        m_direction.CopyVector2(newDirection);

        // Init new position
        nextPos = InitNextPos(deltaTime);
    }
    

    //Set X, Y new position / direction
    m_pos.CopyVector2(nextPos);
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
