#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{

private:
    Maths::Vector2 m_position;
    int m_radius;

public:
    SphereCollider(Maths::Vector2 position, float radius);

    virtual bool CheckCollision(const Collider* other)const override;

    Maths::Vector2 GetPosition() const override;
    int GetRadius() const;
};

