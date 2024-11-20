#include "ColliderManager.h"

#include <iostream>

#include "AWindow.h"
#include "Collider.h"
#include "BoxCollider.h"

ColliderManager::~ColliderManager()
{    // Libérer la mémoire des colliders gérés (si la gestion est propriétaire)
    for (Collider* collider : m_colliders) {
        delete collider;
    }
    m_colliders.clear();
}

void ColliderManager::InitBounds(int widthWindow, int heightWindow)
{
    int sizeBounds = 10; 

    BoxCollider* boxTop = new BoxCollider(Maths::Vector2(widthWindow / 2, 0), widthWindow, sizeBounds);
    m_bounds.push_back(boxTop);
    m_boundNormals.push_back(Maths::Vector2(0.0f, 1.0f));

    BoxCollider* boxBottom = new BoxCollider(Maths::Vector2(widthWindow / 2, heightWindow), widthWindow, sizeBounds);
    m_bounds.push_back(boxBottom);
    m_boundNormals.push_back(Maths::Vector2(0.0f, -1.0f));

    BoxCollider* boxLeft = new BoxCollider(Maths::Vector2(0, heightWindow / 2), sizeBounds, heightWindow);
    m_bounds.push_back(boxLeft);
    m_boundNormals.push_back(Maths::Vector2(1.0f, 0.0f));

    BoxCollider* boxRight = new BoxCollider(Maths::Vector2(widthWindow, heightWindow / 2), sizeBounds, heightWindow);
    m_bounds.push_back(boxRight);
    m_boundNormals.push_back(Maths::Vector2(-1.0f, 0.0f));
}

// Ajouter un collider au système
void ColliderManager::AddCollider(Collider* collider) 
{
    m_colliders.push_back(collider);
}

// Supprimer un collider spécifique
void ColliderManager::RemoveCollider(Collider* collider) 
{
    m_colliders.erase(
        std::remove(m_colliders.begin(), m_colliders.end(), collider),
        m_colliders.end()
    );
}

// Vérification des collisions entre tous les colliders
void ColliderManager::CheckAllCollisions() const 
{
    for (size_t i = 0; i < m_colliders.size(); ++i) 
    {
        for (size_t j = i + 1; j < m_colliders.size(); ++j) 
        {
            if (m_colliders[i]->CheckCollision(m_colliders[j])) 
            {
                std::cout << "Collision detected between Collider "
                    << i << " and Collider " << j << "!" << std::endl;
            }
        }
    }
}

// Vérification des collisions entre tous les colliders
void ColliderManager::CheckAllCollisionsWithBounds() const 
{
    for (size_t i = 0; i < m_colliders.size(); ++i) 
    {
        for (size_t j = 0; j < m_bounds.size(); ++j) 
        {
            if (m_colliders[i]->CheckCollision(m_bounds[j]))
            {
                // Récupérer la position de la balle et sa direction
                auto ballPos = m_colliders[i]->GetPosition();
                Maths::Vector2 ballVelocity = m_colliders[i]->GetVelocity(); // Vitesse de la balle, représentée par un vecteur 2D

                // Récupérer la normale de ce bord à partir du tableau
                Maths::Vector2 normal = m_boundNormals[j];

                float scalarProduct = Maths::Vector2::Scalar(ballVelocity, normal);

                // Calcul du rebond selon la formule : V_reflected = V - 2 * (V . N) * N
                float reflectedX = ballVelocity.GetX() - 2.0f * scalarProduct * normal.GetX();
                float reflectedY = ballVelocity.GetY() - 2.0f * scalarProduct * normal.GetY();
                Maths::Vector2 reflectedVelocity = Maths::Vector2(reflectedX, reflectedY);

                // Appliquer la nouvelle direction à la balle
                m_colliders[i]->SetVelocity(reflectedVelocity);

                std::cout << "[COLLISION] ball position: "
                    << ballPos.GetX() << ", " << ballPos.GetY() << " velocity: "
                    << ballVelocity.GetX() << ", " << ballVelocity.GetY() << std::endl;

                std::cout << "Normal used: " << normal.GetX() << ", " << normal.GetY() << std::endl;
            }
        }
    }
}

// Appeler la fonction de débogage de tous les colliders
void ColliderManager::DrawDebugAll(AWindow* window) 
{
    for (Collider* bound : m_bounds) {
        bound->DrawDebug(window);
    }

    for (Collider* collider : m_colliders) {
        collider->DrawDebug(window);
    }
}