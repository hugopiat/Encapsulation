#pragma once
#include "Vector2.h"
#include <vector>

class AWindow; 

enum class CollisionType
{
    Wall = 0,
    Ball,
    Brick,
    Size
};

class Collider
{

public:
    Maths::Vector2 m_position;
    Maths::Vector2 m_direction;
    float m_velocity;

    Maths::Vector2 m_normalIntersection;

    CollisionType m_collisionType;
    std::vector<CollisionType> m_collisionTypeTargets;

    Collider();
    
    virtual ~Collider() = default;

    // Vérifie la collision avec un autre collider
    virtual bool CheckCollision(Collider* other) = 0;

    // Obtient la position du collider
    virtual Maths::Vector2 GetPosition() const = 0;
    virtual void SetColliderPos(const Maths::Vector2 newPos) = 0;

    // Obtient la velocity du collider
    virtual Maths::Vector2 GetDirection() const = 0;
    virtual void SetDirection(const Maths::Vector2 newPos) = 0;

    // Obtient la position du collider
    virtual void DrawDebug(AWindow* window) = 0;

    // Init all collision target
    virtual void InitAllCollisionTypeTarget();

    // Init all collision target
    virtual void RemovedAllTypeTarget();

    // Init all collision target
    virtual void RemovedCollisionTypeTarget(CollisionType collisionType);

    // Init all collision target
    virtual void AddCollisionTypeTarget(CollisionType collisionType);

    // Init all collision target
    virtual bool IsInCollisionTypeTargets(CollisionType collisionType);

    // Init all collision target
    virtual Maths::Vector2 GetNormal();

    // Init all collision target
    virtual void SetNormal(const Maths::Vector2& normal);

    // Init all collision target
    virtual void SetNormalBounds(int dx, int dy);

};

