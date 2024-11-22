#pragma once
#include "Vector2.h"
#include <vector>
#include <functional>

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
    using CollisionCallback = std::function<void(Collider&)>;

    Maths::Vector2 m_position;
    Maths::Vector2 m_direction;
    float m_velocity;

    Maths::Vector2 m_normalIntersection;

    CollisionType m_collisionType;
    std::vector<CollisionType> m_collisionTypeTargets;

    Collider();
    virtual ~Collider() = default;

    void* GetOwner() const;
    void SetOwner(void* owner);

    // Vérifie la collision avec un autre collider
    virtual bool CheckCollision(Collider* other) = 0;
    virtual bool ResolveCollision(Collider* other) = 0;

    // Obtient la position du collider
    virtual void DrawDebug(AWindow* window) = 0;

    // Obtient la position du collider
    virtual Maths::Vector2 GetPosition() const = 0;
    virtual void SetPosition(const Maths::Vector2 newPos) = 0;

    // Obtient la velocity du collider
    virtual Maths::Vector2 GetDirection() const = 0;
    virtual void SetDirection(const Maths::Vector2 newPos) = 0;

    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;

    // Init / Removed all collision target
    virtual void InitAllCollisionTypeTarget();
    virtual void RemovedAllTypeTarget();

    // Init / Removed one collision target
    virtual void AddCollisionTypeTarget(CollisionType collisionType);
    virtual void RemovedCollisionTypeTarget(CollisionType collisionType);

    virtual void SetOnCollisionEnterCallback(CollisionCallback callback);
    virtual void TriggerOnCollisionEnter(Collider& other);

    // Init all collision target
    virtual bool IsACollisionTypeTarget(CollisionType collisionType);

    // Get / Set normal
    virtual Maths::Vector2 GetNormal();
    virtual void SetNormal(Maths::Vector2 normal);

private:
    CollisionCallback m_onCollisionEnter;
    void* m_owner;
};

