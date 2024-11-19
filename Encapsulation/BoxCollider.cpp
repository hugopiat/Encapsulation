#include "BoxCollider.h"
#include "SphereCollider.h"

BoxCollider::BoxCollider(Maths::Vector2 position, int width, int height) :
	m_position(position), 
	m_width(width), 
	m_height(height)
{
}

Maths::Vector2 BoxCollider::GetPosition() const
{
	return m_position;
}

bool BoxCollider::CheckCollision(const Collider* other) const
{
    if (const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(other)) {
        // Vérifie si la sphère est en collision avec le rectangle
        int closestX = Clamp(sphere->GetPosition().GetX(), GetPosition().GetX(), GetPosition().GetX() + m_width);
        int closestY = Clamp(sphere->GetPosition().GetY(), GetPosition().GetY(), GetPosition().GetY() + m_height);

        int dx = sphere->GetPosition().GetX() - closestX;
        int dy = sphere->GetPosition().GetY() - closestY;

        return (dx * dx + dy * dy) < (sphere->GetRadius() * sphere->GetRadius());
    }
    else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {
        // Vérifie la collision entre deux rectangles
        return !(GetPosition().GetX() + m_width < box->GetPosition().GetX() ||
            GetPosition().GetX() > box->GetPosition().GetX() + box->m_width ||
            GetPosition().GetY() + m_height < box->GetPosition().GetY() ||
            GetPosition().GetY() > box->GetPosition().GetY() + box->m_height);
    }
    return false;
}

int BoxCollider::Clamp(int value, int min, int max) const
{
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
