#pragma once
#include "Collider.h"

class AWindow;
class WindowSDL;

class BoxCollider : public Collider
{
public:
    BoxCollider(Maths::Vector2 position, int width, int height, Maths::Vector2 velocity = Maths::Vector2(0,0));

    virtual Maths::Vector2 GetPosition() const override;
    virtual void SetColliderPos(const Maths::Vector2 newPos) override;

    virtual Maths::Vector2 GetDirection() const override;
    virtual void SetDirection(const Maths::Vector2 newVelocity) override;

    virtual bool CheckCollision(Collider* other) override;
    virtual void DrawDebug(AWindow* window) override;

    bool CheckBoxCollision(const BoxCollider* box);
    void DrawSDL(WindowSDL* windowSDL);
    void DrawRaylib();

private:

    int m_width;
    int m_height;
};
