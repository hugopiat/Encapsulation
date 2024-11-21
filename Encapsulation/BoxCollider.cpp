#include "BoxCollider.h"

#include <SDL2/SDL.h>
#include <cmath>

#include "WindowSDL.h"
#include "WindowRaylib.h"
#include "SphereCollider.h"
#include "Utils.h"
#include <raylib.h>

BoxCollider::BoxCollider(Maths::Vector2 position, int width, int height, Maths::Vector2 velocity) :
    Collider(),
	m_width(width), 
	m_height(height)
{
    SetColliderPos(position);
    SetDirection(velocity);
}

Maths::Vector2 BoxCollider::GetPosition() const
{
	return m_position;
}

void BoxCollider::SetColliderPos(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

Maths::Vector2 BoxCollider::GetDirection() const
{
    return m_direction;
}

void BoxCollider::SetDirection(const Maths::Vector2 newVelocity)
{
    m_direction = newVelocity;
}

bool BoxCollider::CheckCollision(Collider* other)
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

        if (distanceSquared <= RadiuqSquared)
        {
            SetNormalBounds(dx, dy);
            return true;
        }

        return false;
    }

    // Collision avec un autre BoxCollider
    else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other))
    {
        return CheckBoxCollision(box);
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
        DrawSDL(windowSDL);
    }

    WindowRaylib* windowRAYLIB = dynamic_cast<WindowRaylib*>(window);
    if(windowRAYLIB)
    {
        DrawRaylib();
    }
}

bool BoxCollider::CheckBoxCollision(const BoxCollider* box)
{
    float boxPosX = box->GetPosition().GetX();
    float boxPosY = box->GetPosition().GetY();
    float thisPosX = GetPosition().GetX();
    float thisPosY = GetPosition().GetY();

    // Récupérer les positions et dimensions du rectangle (box) à comparer
    float boxLeft = boxPosX - (box->m_width / 2);
    float thisRight = thisPosX + (m_width / 2);
    if (!(thisRight <= boxLeft))
    {
        return false;
    }

    float boxRight = boxPosX + (box->m_width / 2);
    float thisLeft = thisPosX - (m_width / 2);
    if (!(thisRight <= boxLeft))
    {
        return false;
    }

    float boxTop = boxPosY - (box->m_height / 2);
    float thisBottom = thisPosY + (m_height / 2);
    if (!(thisBottom <= boxTop))
    {
        return false;
    }

    float boxBottom = boxPosY + (box->m_height / 2);
    float thisTop = thisPosY - (m_height / 2);
    if (!(thisTop >= boxBottom))
    {
        return false;
    }
    // Si aucune des conditions ci-dessus n'est remplie, les boîtes se chevauchent
    // Calcul de la direction entre la box et le point le plus proche de l'autre box
    float dx = boxPosX - thisPosX;
    float dy = boxPosY - thisPosY;

    SetNormalBounds(dx, dy);
    return true;
}

void BoxCollider::DrawSDL(WindowSDL* windowSDL)
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
}

void BoxCollider::DrawRaylib()
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
