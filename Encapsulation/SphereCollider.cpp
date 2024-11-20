#include "SphereCollider.h"
#include "BoxCollider.h"
#include <cmath>

SphereCollider::SphereCollider(Maths::Vector2 position, float radius) :
    m_position(position),
    m_radius(radius)
{

}

int SphereCollider::GetRadius() const
{
    return m_radius;
}

bool SphereCollider::CheckCollision(const Collider* other) const
{
    if (const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(other)) {
        // Calculer la distance entre les centres des deux sphères
        float dx = GetPosition().GetX() - sphere->GetPosition().GetX();
        float dy = GetPosition().GetY() - sphere->GetPosition().GetY();
        float distance = std::sqrt(dx * dx + dy * dy);
        return distance < (m_radius + sphere->m_radius);
    }
    else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {
        // Si c'est un BoxCollider, tu peux gérer la collision avec un rectangle ici.
        return box->CheckCollision(this);  // Appel au BoxCollider pour vérifier
    }
    return false;
}

Maths::Vector2 SphereCollider::GetPosition() const
{
	return m_position;
}

void SphereCollider::SetColliderPos(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

void SphereCollider::DrawDebug() const
{

}
