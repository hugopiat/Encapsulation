#pragma once
#include "Vector2.h"

class AWindow; 

class Collider
{

public:
    Maths::Vector2 m_position;
    Maths::Vector2 m_velocity;

    virtual ~Collider() = default;

    // Vérifie la collision avec un autre collider
    virtual bool CheckCollision(const Collider* other)const = 0;

    // Obtient la position du collider
    virtual Maths::Vector2 GetPosition() const = 0;
    virtual void SetColliderPos(const Maths::Vector2 newPos) = 0;

    // Obtient la velocity du collider
    virtual Maths::Vector2 GetVelocity() const = 0;
    virtual void SetVelocity(const Maths::Vector2 newPos) = 0;

    // Obtient la position du collider
    virtual void DrawDebug(AWindow* window) = 0;

};

