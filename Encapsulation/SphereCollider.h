#pragma once
#include "Collider.h"

class AWindow;
class WindowSDL;

class SphereCollider : public Collider
{

private:
    int m_radius;

public:
    SphereCollider(Maths::Vector2 position, float radius, Maths::Vector2 velocity = Maths::Vector2(0, 0));

    int GetRadius() const;

    virtual Maths::Vector2 GetPosition() const override;
    virtual void SetColliderPos(const Maths::Vector2 newPos) override;

    virtual Maths::Vector2 GetDirection() const override;
    virtual void SetDirection(const Maths::Vector2 newVelocity) override;

    virtual bool CheckCollision(Collider* other) override;
    virtual void DrawDebug(AWindow* window) override;

    void DrawSDL(WindowSDL* windowSDL);
    void DrawRaylib();
};

