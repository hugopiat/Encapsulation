#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Maths::Vector2 position, int width, int height);

    Maths::Vector2 GetPosition() const override;
    virtual bool CheckCollision(const Collider* other)const override;

    int Clamp(int value, int min, int max) const;

private:

    Maths::Vector2 m_position;
    int m_width;
    int m_height;
};
