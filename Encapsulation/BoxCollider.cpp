#include "BoxCollider.h"

#include <SDL2/SDL.h>
#include <cmath>

#include "WindowSDL.h"
#include "WindowRaylib.h"
#include "SphereCollider.h"
#include "Utils.h"
#include <raylib.h>

BoxCollider::BoxCollider(Maths::Vector2 position, int width, int height, Maths::Vector2 velocity) :
	m_width(width), 
	m_height(height)
{
    SetColliderPos(position);
    SetVelocity(velocity);
}

Maths::Vector2 BoxCollider::GetPosition() const
{
	return m_position;
}

void BoxCollider::SetColliderPos(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

Maths::Vector2 BoxCollider::GetVelocity() const
{
    return m_velocity;
}

void BoxCollider::SetVelocity(const Maths::Vector2 newVelocity)
{
    m_velocity = newVelocity;
}

bool BoxCollider::CheckCollision(const Collider* other) const
{
    // Collision avec un SphereCollider
    if (const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(other))
    {
        // Calcul du point le plus proche du centre de la sphère dans le rectangle
        float closestX = Maths::Utils::Clamp(
            sphere->GetPosition().GetX(),
            GetPosition().GetX() - (m_width / 2),
            GetPosition().GetX() + (m_width / 2)
        );

        float closestY = Maths::Utils::Clamp(
            sphere->GetPosition().GetY(),
            GetPosition().GetY() - (m_height / 2),
            GetPosition().GetY() + (m_height / 2)
        );

        // Calcul de la distance entre la sphère et le point le plus proche
        float dx = sphere->GetPosition().GetX() - closestX;
        float dy = sphere->GetPosition().GetY() - closestY;

        float distanceSquared = dx * dx + dy * dy;
        float RadiuqSquared = (sphere->GetRadius() * sphere->GetRadius());

        return distanceSquared <= RadiuqSquared;
    }

    // Collision avec un autre BoxCollider
    else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other))
    {
        // Récupérer les positions et dimensions du rectangle (box) à comparer
        float boxLeft = box->GetPosition().GetX() - (box->m_width / 2);
        float thisRight = GetPosition().GetX() + (m_width / 2);
        if (!(thisRight <= boxLeft)) 
        {
            return false;
        }

        float boxRight = box->GetPosition().GetX() + (box->m_width / 2);
        float thisLeft = GetPosition().GetX() - (m_width / 2);
        if (!(thisRight <= boxLeft))
        {
            return false;
        }

        float boxTop = box->GetPosition().GetY() - (box->m_height / 2);
        float thisBottom = GetPosition().GetY() + (m_height / 2);
        if (!(thisBottom <= boxTop))
        {
            return false;
        }

        float boxBottom = box->GetPosition().GetY() + (box->m_height / 2);
        float thisTop = GetPosition().GetY() - (m_height / 2);
        if (!(thisTop >= boxBottom))
        {
            return false;
        }

        // Si aucune des conditions ci-dessus n'est remplie, les boîtes se chevauchent
        return true;
    }

    // Si l'autre collider n'est ni une sphère, ni un rectangle
    return false;
}

void BoxCollider::DrawDebug(AWindow* window)
{
    // Convertir l'argument window en WindowSDL
    WindowSDL* windowSDL = dynamic_cast<WindowSDL*>(window);
    if (windowSDL)
    {
        // Obtenir le renderer de la fenêtre
        SDL_Renderer* renderer = windowSDL->GetRenderer();

        // Définir la couleur pour le débogage (par exemple, un bleu semi-transparent)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 128); // Bleu avec transparence (alpha = 128)

        // Dessiner le rectangle représentant le BoxCollider
        // Note : m_position est le coin supérieur gauche du rectangle, et m_width et m_height sont ses dimensions.
        SDL_Rect colliderRect = {
            static_cast<int>(GetPosition().GetX() - m_width / 2),       // X : position X du coin supérieur gauche
            static_cast<int>(GetPosition().GetY() - m_height / 2),       // Y : position Y du coin supérieur gauche
            static_cast<int>(m_width),                    // Largeur du collider
            static_cast<int>(m_height)                    // Hauteur du collider
        };

        // Dessiner le rectangle
        SDL_RenderDrawRect(renderer, &colliderRect); // Dessine le contour du rectangle

        // Si vous souhaitez remplir le rectangle, utilisez SDL_RenderFillRect
        SDL_RenderFillRect(renderer, &colliderRect);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        return;
    }

    WindowRaylib* windowRAYLIB = dynamic_cast<WindowRaylib*>(window);
    if(windowRAYLIB)
    {
        Color debugColor = { 0, 0, 255, 128 }; // Bleu avec transparence (alpha = 128)

        // Calculer les coordonnées du rectangle de débogage
        float rectX = GetPosition().GetX() - m_width / 2; // X : position du coin supérieur gauche
        float rectY = GetPosition().GetY() - m_height / 2; // Y : position du coin supérieur gauche
        float rectWidth = m_width;  // Largeur du collider
        float rectHeight = m_height; // Hauteur du collider

        // Dessiner le contour du rectangle
        DrawRectangleLinesEx(
            Rectangle{ rectX, rectY, rectWidth, rectHeight }, // Rectangle à dessiner
            1.0f, // Épaisseur des lignes
            debugColor // Couleur de débogage
        );

        // Si vous souhaitez remplir le rectangle
        DrawRectangleRec(
            Rectangle{ rectX, rectY, rectWidth, rectHeight }, // Rectangle à remplir
            debugColor // Couleur de débogage
        );
    }
}
