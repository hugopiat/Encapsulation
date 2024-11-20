#include "Vector2.h"

Maths::Vector2::Vector2() : 
    m_x(0),
    m_y(0)
{
}

Maths::Vector2::Vector2(int x, int y) :
    m_x(x),
    m_y(y)
{
}

void Maths::Vector2::CopyVector2(Vector2& vect2Origin)
{
    SetX(vect2Origin.GetX());
    SetY(vect2Origin.GetY());
}

int Maths::Vector2::GetX() const
{
    return m_x;
}

void Maths::Vector2::SetX(int x)
{
    m_x = x;
}

int Maths::Vector2::GetY() const
{
    return m_y;
}

void Maths::Vector2::SetY(int y)
{
    m_y = y;
}
