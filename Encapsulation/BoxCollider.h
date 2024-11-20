#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:
    BoxCollider(Maths::Vector2 position, int width, int height);

    virtual Maths::Vector2 GetPosition() const override;
    virtual void SetColliderPos(const Maths::Vector2 newPos) override;
    virtual bool CheckCollision(const Collider* other)const override;
    virtual void DrawDebug() const override;

private:

    Maths::Vector2 m_position;
    int m_width;
    int m_height;
};
