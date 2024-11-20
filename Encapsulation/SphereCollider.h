#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{

private:
    Maths::Vector2 m_position;
    int m_radius;

public:
    SphereCollider(Maths::Vector2 position, float radius);

    int GetRadius() const;

    virtual bool CheckCollision(const Collider* other)const override;
    virtual Maths::Vector2 GetPosition() const override;
    virtual void SetColliderPos(const Maths::Vector2 newPos) override;
    virtual void DrawDebug() const override;
};

