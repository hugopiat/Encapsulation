#pragma once
#include <vector>
#include "Vector2.h"

class Collider;
class AWindow;

class ColliderManager
{
private:
    std::vector<Collider*> m_bounds; // Liste des colliders g�r�s
    std::vector<Maths::Vector2> m_boundNormals; // Liste des colliders g�r�s
    std::vector<Collider*> m_colliders; // Liste des colliders g�r�s

public:
    ColliderManager() = default;
    ~ColliderManager();

    void InitBounds(int widthWindow, int heightWindow);

    // Ajouter un collider au syst�me
    void AddCollider(Collider* collider);

    // Supprimer un collider sp�cifique
    void RemoveCollider(Collider* collider);

    // V�rification des collisions entre tous les colliders
    void CheckAllCollisions() const;

    // V�rification des collisions entre tous les colliders
    void CheckAllCollisionsWithBounds() const;

    // Appeler la fonction de d�bogage de tous les colliders
    void DrawDebugAll(AWindow* window);
};

