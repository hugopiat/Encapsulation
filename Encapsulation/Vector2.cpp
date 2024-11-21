#include "Vector2.h"
#include <math.h>

Maths::Vector2::Vector2() : 
    m_x(0),
    m_y(0)
{
}

Maths::Vector2::Vector2(float x, float y) :
    m_x(x),
    m_y(y)
{
}

void Maths::Vector2::Normalize()
{
    if (m_x == 0 && m_y == 0)
    {
        return;
    }
    float ratio = sqrt((m_x * m_x) + (m_y * m_y));
    m_x = (m_x / ratio);
    m_y = (m_y / ratio);
}

float Maths::Vector2::Scalar(const Vector2& origin, const Vector2& second)
{
    return origin.GetX() * second.GetX() + origin.GetY() * second.GetY();
}

float Maths::Vector2::GetX() const
{
    return m_x;
}

void Maths::Vector2::SetX(float x)
{
    m_x = x;
}

float Maths::Vector2::GetY() const
{
    return m_y;
}

void Maths::Vector2::SetY(float y)
{
    m_y = y;
}
