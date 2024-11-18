#include "Vector2.h"

Vector2::Vector2() : 
    m_x(0),
    m_y(0)
{
}

Vector2::Vector2(int x, int y) :
    m_x(x),
    m_y(y)
{
}

int Vector2::GetPositionX()
{
    return m_x;
}

void Vector2::SetPositionX(int x)
{
    m_x = x;
}

int Vector2::GetPositionY()
{
    return m_y;
}

void Vector2::SetPositionY(int y)
{
    m_y = y;
}
