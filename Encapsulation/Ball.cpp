#include "Ball.h"

#include "ASprite.h"
#include "Utils.h"

#include "Collider.h"
#include "SphereCollider.h"

using namespace std::placeholders;

Ball::Ball() :
    m_sprite(nullptr),
    m_sphereCollider(nullptr),
    m_position(0,0),
    m_damage(0)
{

}

void Ball::Init(const Maths::Vector2 pos, const Maths::Vector2 direction, ASprite* sprite, float radius)
{
    m_position = pos;
    m_sprite = sprite;
    m_damage = 1;

    Maths::Vector2 directionNormalize = direction;
    directionNormalize.Normalize();

    m_sphereCollider = new SphereCollider(pos, radius, directionNormalize);
    m_sphereCollider->SetOwner(this);
    m_sphereCollider->m_collisionType = CollisionType::Ball;
    m_sphereCollider->SetOnCollisionEnterCallback(std::bind(&Ball::OnCollisionEnter, this, _1));

    m_sphereCollider->InitAllCollisionTypeTarget();
    m_sphereCollider->RemovedCollisionTypeTarget(CollisionType::Ball);

    m_sprite->SetSizeSprite(Maths::Vector2(radius * 1.5f, radius * 1.5f));
}

void Ball::SetSpeed(float speed)
{
    m_sphereCollider->m_velocity = speed;
}

void Ball::SetPosition(const Maths::Vector2 pos)
{
    m_position = pos;
    m_sphereCollider->SetPosition(m_position);
    m_sprite->SetPositionSprite(m_position);
}

Maths::Vector2 Ball::InitNextPos(float deltaTime)
{
    // Init next pos
    Maths::Vector2 nextPos = Maths::Vector2(
        m_position.GetX() + (deltaTime * m_sphereCollider->m_velocity * m_sphereCollider->GetDirection().GetX()),
        m_position.GetY() + (deltaTime * m_sphereCollider->m_velocity * m_sphereCollider->GetDirection().GetY()));

    return nextPos;
}

void Ball::Update(float deltaTime)
{
    Maths::Vector2 nextPos = InitNextPos(deltaTime);
    SetPosition(nextPos);
}

void Ball::Draw()
{
    m_sprite->Draw();
}

void Ball::OnCollisionEnter(Collider& other)
{
    float closestX = Maths::Utils::Clamp(
        m_sphereCollider->GetPosition().GetX(),
        other.GetPosition().GetX() - other.GetWidth() / 2,
        other.GetPosition().GetX() + other.GetWidth() / 2
    );

    float closestY = Maths::Utils::Clamp(
        m_sphereCollider->GetPosition().GetY(),
        other.GetPosition().GetY() - other.GetHeight() / 2,
        other.GetPosition().GetY() + other.GetHeight() / 2
    );

    float dx = m_sphereCollider->GetPosition().GetX() - closestX;
    float dy = m_sphereCollider->GetPosition().GetY() - closestY;
    float distance = std::sqrt(dx * dx + dy * dy);

    // Calcul de la profondeur de pénétration
    float penetrationDepth = m_sphereCollider->GetRadius() - distance;

    Maths::Vector2 normal = other.GetNormal();
    normal.Normalize();

    // Si la balle est en chevauchement, applique une correction
    if (penetrationDepth > 0) {

        // Ajouter un léger décalage pour éviter l'effet de "collage"
        Maths::Vector2 correctionOffset = normal * (penetrationDepth + 0.1f); // léger décalage ajouté

        // Calculer la nouvelle position de la balle
        Maths::Vector2 newPosition = m_sphereCollider->GetPosition() + correctionOffset;
        m_sphereCollider->SetPosition(newPosition);
        SetPosition(newPosition); // Mettre à jour la position de la balle
    }

    Maths::Vector2 ballDirection = m_sphereCollider->GetDirection();
    ballDirection.Normalize();

    float scalarProduct = Maths::Vector2::Scalar(ballDirection, normal);

    Maths::Vector2 reflectedDirection = Maths::Vector2(
        ballDirection.GetX() - 2.0f * scalarProduct * normal.GetX(),
        ballDirection.GetY() - 2.0f * scalarProduct * normal.GetY()
    );

    reflectedDirection.Normalize();
    m_sphereCollider->SetDirection(reflectedDirection);

    std::cout << "[BALL] Nouvelle direction : " << reflectedDirection.GetX() << ", " << reflectedDirection.GetY() << " !\n";
}

Collider* Ball::GetCollider()
{
    return m_sphereCollider;
}
