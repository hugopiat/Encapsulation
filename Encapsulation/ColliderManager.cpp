#include "ColliderManager.h"

#include <iostream>

#include "AWindow.h"
#include "ASprite.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Wall.h"

ColliderManager::~ColliderManager()
{    // Libérer la mémoire des colliders gérés (si la gestion est propriétaire)
    for (Collider* collider : m_colliders) {
        delete collider;
    }
    m_colliders.clear();
}

std::vector<Wall*> ColliderManager::InitWalls(AWindow* window, ASprite* sprite)
{
    int sizeBounds = 10; 

    std::vector<Wall*> walls = std::vector<Wall*>();
    Wall* newWall = new Wall();
    newWall->CreateWall(sprite, Maths::Vector2(window->m_width / 2, 0), window->m_width, sizeBounds);
    m_colliders.push_back(newWall->GetCollider());
    walls.push_back(newWall);

    newWall = new Wall();
    newWall->CreateWall(sprite, Maths::Vector2(window->m_width / 2, window->m_height), window->m_width, sizeBounds);
    m_colliders.push_back(newWall->GetCollider());
    walls.push_back(newWall);

    newWall = new Wall();
    newWall->CreateWall(sprite, Maths::Vector2(0, window->m_height / 2), sizeBounds, window->m_height);
    m_colliders.push_back(newWall->GetCollider());
    walls.push_back(newWall);

    newWall = new Wall();
    newWall->CreateWall(sprite, Maths::Vector2(window->m_width, window->m_height / 2), sizeBounds, window->m_height);
    m_colliders.push_back(newWall->GetCollider());
    walls.push_back(newWall);

    return walls;
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
            if (!m_colliders[i]->IsACollisionTypeTarget(m_colliders[j]->m_collisionType) && !m_colliders[j]->IsACollisionTypeTarget(m_colliders[i]->m_collisionType))
            {
                continue;
            }

            if (m_colliders[i]->CheckCollision(m_colliders[j]))
            {
                m_colliders[i]->ResolveCollision(m_colliders[j]);
                m_colliders[j]->ResolveCollision(m_colliders[i]);

                m_colliders[i]->TriggerOnCollisionEnter(*m_colliders[j]);
                m_colliders[j]->TriggerOnCollisionEnter(*m_colliders[i]);
            }
        }
    }
}

// Appeler la fonction de débogage de tous les colliders
void ColliderManager::DrawDebugAll(AWindow* window) 
{
    for (Collider* collider : m_colliders) {
        collider->DrawDebug(window);
    }
}