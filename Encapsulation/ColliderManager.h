#pragma once
#include <vector>
#include "Vector2.h"

class Collider;
class AWindow;
class ASprite;
class Wall;

class ColliderManager
{
private:
    std::vector<Collider*> m_colliders; // Liste des colliders gérés

public:
    ColliderManager() = default;
    ~ColliderManager();

    std::vector<Wall*> InitWalls(AWindow* window, ASprite* sprite);

    // Ajouter un collider au système
    void AddCollider(Collider* collider);

    // Supprimer un collider spécifique
    void RemoveCollider(Collider* collider);

    // Vérification des collisions entre tous les colliders
    void CheckAllCollisions() const;

    // Appeler la fonction de débogage de tous les colliders
    void DrawDebugAll(AWindow* window);
};

