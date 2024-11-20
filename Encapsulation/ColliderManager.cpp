#include "ColliderManager.h"
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
    BoxCollider* boxTop = new BoxCollider(Maths::Vector2(widthWindow / 2, 0), widthWindow, 5);
    BoxCollider* boxBottom = new BoxCollider(Maths::Vector2(widthWindow / 2, heightWindow), widthWindow, 5);

    BoxCollider* boxLeft = new BoxCollider(Maths::Vector2(0, heightWindow / 2), 5, heightWindow);
    BoxCollider* boxRight = new BoxCollider(Maths::Vector2(widthWindow, heightWindow / 2), 5, heightWindow);

    m_bounds.push_back(boxTop);
    m_bounds.push_back(boxBottom);

    m_bounds.push_back(boxLeft);
    m_bounds.push_back(boxRight);
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
        for (size_t j = i + 1; j < m_bounds.size(); ++j) 
        {
            if (m_colliders[i]->CheckCollision(m_bounds[j]))
            {
                std::cout << "Collision detected between Colliders "
                    << i << " and bounds " << j << "!" << std::endl;
            }
        }
    }
}

// Appeler la fonction de débogage de tous les colliders
void ColliderManager::DrawDebugAll() const 
{
    for (const Collider* collider : m_colliders) {
        collider->DrawDebug();
    }
}