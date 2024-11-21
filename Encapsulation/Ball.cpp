#include "Ball.h"

#include "ASprite.h"
#include "Utils.h"

#include "Collider.h"
#include "SphereCollider.h"

Ball::Ball() :
    m_sprite(nullptr),
    m_sphereCollider(nullptr),
    m_pos(0,0)
{

}

void Ball::Init(const Maths::Vector2 pos, const Maths::Vector2 direction, ASprite* sprite, float radius)
{
    m_pos = pos;
    m_sprite = sprite;

    Maths::Vector2 directionNormalize = direction;
    directionNormalize.Normalize();
    m_sphereCollider = new SphereCollider(pos, radius, directionNormalize);

    m_sphereCollider->m_collisionType = CollisionType::Ball;
    m_sphereCollider->InitAllCollisionTypeTarget();
    m_sphereCollider->RemovedCollisionTypeTarget(CollisionType::Ball);
    m_sprite->SetSizeSprite(Maths::Vector2(radius, radius));
}

void Ball::SetSpeed(float speed)
{
    m_sphereCollider->m_velocity = speed;
}

Maths::Vector2 Ball::InitNextPos(float deltaTime)
{
    // Init next pos
    Maths::Vector2 nextPos = Maths::Vector2(
        m_pos.GetX() + (deltaTime * m_sphereCollider->m_velocity * m_sphereCollider->GetDirection().GetX()),
        m_pos.GetY() + (deltaTime * m_sphereCollider->m_velocity * m_sphereCollider->GetDirection().GetY()));

    return nextPos;
}

void Ball::Update(float deltaTime, int windowWidth, int windowHeight)
{
    Maths::Vector2 nextPos = InitNextPos(deltaTime);
    m_pos = nextPos;
    m_sphereCollider->SetColliderPos(nextPos);
}

void Ball::Draw()
{
    m_sprite->SetPositionSprite(m_pos);
    m_sprite->Draw();
}

Collider* Ball::GetCollider()
{
    return m_sphereCollider;
}
