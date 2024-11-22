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
    SetPosition(position);
    SetDirection(velocity);
}

int BoxCollider::GetWidth() const
{
    return m_width;
}

int BoxCollider::GetHeight() const
{
    return m_height;
}

Maths::Vector2 BoxCollider::GetPosition() const
{
	return m_position;
}

void BoxCollider::SetPosition(const Maths::Vector2 newPos)
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
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(other))
    {
        return CheckSphereCollision(sphere);
    }

    // Collision avec un autre BoxCollider
    else if (BoxCollider* box = dynamic_cast<BoxCollider*>(other))
    {
        return CheckBoxCollision(box);
    }

    // Si l'autre collider n'est ni une sphère, ni un rectangle
    return false;
}

bool BoxCollider::ResolveCollision(Collider* other)
{
    // Résolution de collision avec un SphereCollider
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(other))
    {
        // Calcule la direction et la profondeur de pénétration
        float closestX = Maths::Utils::Clamp(
            sphere->GetPosition().GetX(),
            GetPosition().GetX() - (GetWidth() / 2),
            GetPosition().GetX() + (GetWidth() / 2)
        );

        float closestY = Maths::Utils::Clamp(
            sphere->GetPosition().GetY(),
            GetPosition().GetY() - (GetHeight() / 2),
            GetPosition().GetY() + (GetHeight() / 2)
        );

        float dx = sphere->GetPosition().GetX() - closestX;
        float dy = sphere->GetPosition().GetY() - closestY;

        Maths::Vector2 direction(dx, dy);

        if (dx == 0 && dy == 0) {

            float deltaX = Maths::Utils::ABS(GetPosition().GetX() - sphere->GetPosition().GetX());
            float deltaY = Maths::Utils::ABS(GetPosition().GetY() - sphere->GetPosition().GetY());

            if (deltaX > deltaY) {
                // Si la balle est plus proche sur l'axe Y, rebond sur l'axe X
                direction = Maths::Vector2((GetPosition().GetX() < sphere->GetPosition().GetX()) ? -1.0f : 1.0f, 0);
            }
            else {
                // Sinon, rebond sur l'axe Y
                direction = Maths::Vector2(0, (GetPosition().GetY() < sphere->GetPosition().GetY()) ? -1.0f : 1.0f);
            }
        }

        direction.Normalize();

        // Mise à jour des normales
        SetNormal(direction);
        sphere->SetNormal(direction * -1);  // Inverser la direction pour la boîte

        return true;
    }

    // Résolution de collision avec un autre BoxCollider
    else if (BoxCollider* box = dynamic_cast<BoxCollider*>(other))
    {
        // Calcul de la direction de collision
        float dx = GetPosition().GetX() - box->GetPosition().GetX();
        float dy = GetPosition().GetY() - box->GetPosition().GetY();

        Maths::Vector2 direction(0, 0);

        // Déterminer quelle face est en collision
        if (Maths::Utils::ABS(dx) > Maths::Utils::ABS(dy)) // Collision avec les faces gauche ou droite
        {
            if (dx < 0)
            {
                direction += Maths::Vector2(-1, 0); // Face gauche
            }
            else
            {
                direction += Maths::Vector2(1, 0); // Face gauche
            }
        }
        else // Collision avec les faces haut ou bas
        {
            if (dy < 0)
            {
                direction += Maths::Vector2(0, -1); // Face gauche
            }
            else
            {
                direction += Maths::Vector2(0, 1); // Face gauche
            }
        }

        // Mise à jour de la direction
        direction.Normalize();

        SetNormal(direction);  // Face haut
        box->SetNormal(direction * -1); // Face bas

        return true;
    }

    return false;
}

bool BoxCollider::CheckBoxCollision(BoxCollider* box)
{
    float boxPosX = box->GetPosition().GetX();
    float boxPosY = box->GetPosition().GetY();
    float thisPosX = GetPosition().GetX();
    float thisPosY = GetPosition().GetY();

    float boxLeft = boxPosX - (box->m_width / 2);
    float thisRight = thisPosX + (m_width / 2);
    if (thisRight <= boxLeft) return false;

    float boxRight = boxPosX + (box->m_width / 2);
    float thisLeft = thisPosX - (m_width / 2);
    if (thisLeft >= boxRight) return false;

    float boxTop = boxPosY - (box->m_height / 2);
    float thisBottom = thisPosY + (m_height / 2);
    if (thisBottom <= boxTop) return false;

    float boxBottom = boxPosY + (box->m_height / 2);
    float thisTop = thisPosY - (m_height / 2);
    if (thisTop >= boxBottom) return false;

    return true;
}

bool BoxCollider::CheckSphereCollision(SphereCollider* sphere)
{
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

    float dx = sphere->GetPosition().GetX() - closestX;
    float dy = sphere->GetPosition().GetY() - closestY;

    float distanceSquared = dx * dx + dy * dy;
    float radiusSquared = sphere->GetRadius() * sphere->GetRadius();

    return distanceSquared <= radiusSquared;
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
    if (windowRAYLIB)
    {
        DrawRaylib();
    }
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
