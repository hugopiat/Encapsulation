#pragma once
#include "Collider.h"

class AWindow;

class BoxCollider : public Collider
{
public:
    BoxCollider(Maths::Vector2 position, int width, int height, Maths::Vector2 velocity = Maths::Vector2(0,0));

    virtual Maths::Vector2 GetPosition() const override;
    virtual void SetColliderPos(const Maths::Vector2 newPos) override;

    virtual Maths::Vector2 GetVelocity() const override;
    virtual void SetVelocity(const Maths::Vector2 newVelocity) override;

    virtual bool CheckCollision(const Collider* other)const override;
    virtual void DrawDebug(AWindow* window) override;

private:

    int m_width;
    int m_height;
};
