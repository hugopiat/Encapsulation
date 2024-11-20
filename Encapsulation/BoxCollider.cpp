#include "BoxCollider.h"
#include "SphereCollider.h"
#include <cmath>

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

void BoxCollider::SetColliderPos(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

bool BoxCollider::CheckCollision(const Collider* other) const
{
    if (const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(other)) {

        float rectCenterX = GetPosition().GetX();
        float rectCenterY = GetPosition().GetY();

        // Centre de la sphère
        float sphereCenterX = sphere->GetPosition().GetX();
        float sphereCenterY = sphere->GetPosition().GetY();

        // Calcul de la direction du centre du rectangle à partir du centre de la sphère
        float directionX = rectCenterX - sphereCenterX;
        float directionY = rectCenterY - sphereCenterY;

        // Normaliser la direction pour avoir un vecteur unitaire
        float length = sqrt(directionX * directionX + directionY * directionY);
        directionX /= length;
        directionY /= length;

        // Calculer le point à la surface du cercle dans cette direction
        float intersectionX = sphereCenterX + directionX * sphere->GetRadius();
        float intersectionY = sphereCenterY + directionY * sphere->GetRadius();

        // Vérifier si ce point est dans le rectangle
        bool isInsideRectangle =
            intersectionX >= GetPosition().GetX() &&
            intersectionX <= (GetPosition().GetX() + m_width) &&
            intersectionY >= GetPosition().GetY() &&
            intersectionY <= (GetPosition().GetY() + m_height);

        return isInsideRectangle;
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

void BoxCollider::DrawDebug() const
{

}
