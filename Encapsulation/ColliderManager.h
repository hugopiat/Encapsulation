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
    std::vector<Collider*> m_colliders; // Liste des colliders g�r�s

public:
    ColliderManager() = default;
    ~ColliderManager();

    std::vector<Wall*> InitWalls(AWindow* window, ASprite* sprite);

    // Ajouter un collider au syst�me
    void AddCollider(Collider* collider);

    // Supprimer un collider sp�cifique
    void RemoveCollider(Collider* collider);

    // V�rification des collisions entre tous les colliders
    void CheckAllCollisions() const;

    // Appeler la fonction de d�bogage de tous les colliders
    void DrawDebugAll(AWindow* window);
};

