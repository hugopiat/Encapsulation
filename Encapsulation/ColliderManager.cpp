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

void ColliderManager::InitWalls(int widthWindow, int heightWindow)
{
    int sizeBounds = 10; 

    //  Bounds
    CreateWall(widthWindow / 2, 0, widthWindow, sizeBounds);
    CreateWall(widthWindow / 2, heightWindow, widthWindow, sizeBounds);
    CreateWall(0, heightWindow / 2, sizeBounds, heightWindow);
    CreateWall(widthWindow, heightWindow / 2, sizeBounds, heightWindow);


    //  Brick
    CreateBrick(widthWindow / 2, heightWindow / 10, sizeBounds * 10, sizeBounds * 10);
    CreateBrick(widthWindow / 2, (heightWindow * 9) / 10, sizeBounds * 10, sizeBounds * 10);
    CreateBrick(widthWindow / 10, heightWindow / 2, sizeBounds * 10, sizeBounds * 10);
    CreateBrick((widthWindow * 9) / 10, heightWindow / 2, sizeBounds * 10, sizeBounds * 10);
}

void ColliderManager::CreateWall(int x, int y, int width, int height)
{
    BoxCollider* box = new BoxCollider(Maths::Vector2(x, y), width, height);
    box->m_collisionType = CollisionType::Wall;
    m_colliders.push_back(box);
}

void ColliderManager::CreateBrick(int x, int y, int width, int height)
{
    BoxCollider* box = new BoxCollider(Maths::Vector2(x, y), width, height);
    box->m_collisionType = CollisionType::Brick;
    m_colliders.push_back(box);
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
        for (size_t j = 0; j < m_colliders.size(); ++j) 
        {
            if (!m_colliders[i]->IsInCollisionTypeTargets(m_colliders[j]->m_collisionType)) 
            {
                continue;
            }

            if (m_colliders[i]->CheckCollision(m_colliders[j])) 
            {
                Maths::Vector2 ballPos = m_colliders[i]->GetPosition();
                Maths::Vector2 ballDirection = m_colliders[i]->GetDirection();
                ballDirection.Normalize();

                Maths::Vector2 normal = m_colliders[j]->GetNormal();
                normal.Normalize();
                float scalarProduct = Maths::Vector2::Scalar(ballDirection, normal);

                Maths::Vector2 reflectedDirection = Maths::Vector2(
                    ballDirection.GetX() - 2.0f * scalarProduct * normal.GetX(),
                    ballDirection.GetY() - 2.0f * scalarProduct * normal.GetY());

                reflectedDirection.Normalize();
                m_colliders[i]->SetDirection(reflectedDirection);

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