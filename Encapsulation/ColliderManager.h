#pragma once
#include <vector>
#include "Vector2.h"

class Collider;
class AWindow;

class ColliderManager
{
private:
    std::vector<Collider*> m_bounds; // Liste des colliders gérés
    std::vector<Maths::Vector2> m_boundNormals; // Liste des colliders gérés
    std::vector<Collider*> m_colliders; // Liste des colliders gérés

public:
    ColliderManager() = default;
    ~ColliderManager();

    void InitBounds(int widthWindow, int heightWindow);

    // Ajouter un collider au système
    void AddCollider(Collider* collider);

    // Supprimer un collider spécifique
    void RemoveCollider(Collider* collider);

    // Vérification des collisions entre tous les colliders
    void CheckAllCollisions() const;

    // Vérification des collisions entre tous les colliders
    void CheckAllCollisionsWithBounds() const;

    // Appeler la fonction de débogage de tous les colliders
    void DrawDebugAll(AWindow* window);
};

