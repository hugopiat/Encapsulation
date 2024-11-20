#include "Ball.h"

#include "ASprite.h"
#include "Utils.h"

#include "Collider.h"
#include "SphereCollider.h"

Ball::Ball() :
    m_sprite(nullptr),
    m_sphereCollider(nullptr),
    m_pos(0,0),
    m_direction(0,0), 
    m_speed(0)
{

}

void Ball::Init(const Maths::Vector2 pos, const Maths::Vector2 direction, ASprite* sprite, float radius)
{
    m_pos = pos;
    m_direction = direction;
    m_direction.Normalize();
    m_sprite = sprite;

    m_sphereCollider = new SphereCollider(pos, radius, m_direction * 10);
    m_sprite->SetSizeSprite(Maths::Vector2(radius, radius));
}

void Ball::SetSpeed(float speed)
{
    m_speed = speed;
}

Maths::Vector2 Ball::InitNextPos(float deltaTime)
{
    // Init next pos
    Maths::Vector2 nextPos = Maths::Vector2(
        m_pos.GetX() + (deltaTime * m_speed * m_sphereCollider->GetVelocity().GetX()),
        m_pos.GetY() + (deltaTime * m_speed * m_sphereCollider->GetVelocity().GetY()));

    return nextPos;
}

bool Ball::CheckCollisionBounds(Maths::Vector2 nextPos, int windowWidth, int windowHeight)
{
    bool collided = false;

    if (nextPos.GetX() <= 0) {
        m_direction.SetX(Maths::Utils::ABS(m_direction.GetX()));
        nextPos.SetX(0);
        collided = true;
    }
    else if (nextPos.GetX() >= windowWidth) {
        m_direction.SetX(-Maths::Utils::ABS(m_direction.GetX()));
        nextPos.SetX(windowWidth);
        collided = true;
    }

    if (nextPos.GetY() <= 0) {
        m_direction.SetY(Maths::Utils::ABS(m_direction.GetY())); 
        nextPos.SetY(0);
        collided = true;
    }
    else if (nextPos.GetY() >= windowHeight) {
        m_direction.SetY(-Maths::Utils::ABS(m_direction.GetY()));
        nextPos.SetY(windowHeight);
        collided = true;
    }

    return collided;
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
