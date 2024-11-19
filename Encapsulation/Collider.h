#pragma once
#include "Vector2.h"

class Collider
{

public:
    virtual ~Collider() = default;

    // Vérifie la collision avec un autre collider
    virtual bool CheckCollision(const Collider* other)const = 0;

    // Obtient la position du collider
    virtual Maths::Vector2 GetPosition() const = 0;

};

