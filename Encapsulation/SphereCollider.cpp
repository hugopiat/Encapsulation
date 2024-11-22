#include "SphereCollider.h"

#include <SDL2/SDL.h>
#include <cmath>

#include "AWindow.h"
#include "WindowSDL.h"
#include "WindowRaylib.h"
#include "BoxCollider.h"
#include <raylib.h>
#include "Utils.h"

SphereCollider::SphereCollider(Maths::Vector2 position, float radius, Maths::Vector2 velocity) :
    Collider(),
    m_radius(radius)
{
    SetPosition(position);
    SetDirection(velocity);
}

int SphereCollider::GetRadius() const
{
    return m_radius;
}

bool SphereCollider::CheckCollision(Collider* other)
{
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(other))
    {
        // Calcul de la distance entre les centres des deux sphères
        float dx = GetPosition().GetX() - sphere->GetPosition().GetX();
        float dy = GetPosition().GetY() - sphere->GetPosition().GetY();

        float distanceSquared = dx * dx + dy * dy;
        float combinedRadius = m_radius + sphere->m_radius;

        return distanceSquared < (combinedRadius * combinedRadius);
    }
    else if (BoxCollider* box = dynamic_cast<BoxCollider*>(other))
    {
        return box->CheckCollision(this);
    }
    return false;
}

bool SphereCollider::ResolveCollision(Collider* other)
{
    // Résolution de collision avec un autre SphereCollider
    if (SphereCollider* sphere = dynamic_cast<SphereCollider*>(other))
    {
        float dx = GetPosition().GetX() - sphere->GetPosition().GetX();
        float dy = GetPosition().GetY() - sphere->GetPosition().GetY();

        Maths::Vector2 direction(dx, dy);

        direction.Normalize();

        SetNormal(direction);
        sphere->SetNormal(direction * -1);
        return true;
    }

    // Résolution de collision avec un BoxCollider
    else if (BoxCollider* box = dynamic_cast<BoxCollider*>(other))
    {
        // Calcule le point le plus proche du centre de la sphère dans le rectangle
        float closestX = Maths::Utils::Clamp(
            GetPosition().GetX(),
            box->GetPosition().GetX() - (box->GetWidth() / 2),
            box->GetPosition().GetX() + (box->GetWidth() / 2)
        );

        float closestY = Maths::Utils::Clamp(
            GetPosition().GetY(),
            box->GetPosition().GetY() - (box->GetHeight() / 2),
            box->GetPosition().GetY() + (box->GetHeight() / 2)
        );

        float dx = GetPosition().GetX() - closestX;
        float dy = GetPosition().GetY() - closestY;

        Maths::Vector2 direction(dx, dy);

        if (dx == 0 && dy == 0) {

            float deltaX = Maths::Utils::ABS(GetPosition().GetX() - box->GetPosition().GetX());
            float deltaY = Maths::Utils::ABS(GetPosition().GetY() - box->GetPosition().GetY());

            if (deltaX > deltaY) {
                // Si la balle est plus proche sur l'axe Y, rebond sur l'axe X
                direction = Maths::Vector2((GetPosition().GetX() < box->GetPosition().GetX()) ? -1.0f : 1.0f, 0);
            }
            else {
                // Sinon, rebond sur l'axe Y
                direction = Maths::Vector2(0, (GetPosition().GetY() < box->GetPosition().GetY()) ? -1.0f : 1.0f);
            }
        }

        direction.Normalize();

        // Mise à jour des normales
        SetNormal(direction * -1);
        box->SetNormal(direction);  // Inverser la direction pour la boîte

        return true;
    }

    return false;
}

Maths::Vector2 SphereCollider::GetPosition() const
{
	return m_position;
}

void SphereCollider::SetPosition(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

Maths::Vector2 SphereCollider::GetDirection() const
{
    return m_direction;
}

void SphereCollider::SetDirection(const Maths::Vector2 newDirection)
{
    m_direction = newDirection;
}

int SphereCollider::GetWidth() const
{
    return GetRadius();
}

int SphereCollider::GetHeight() const
{
    return GetRadius();
}

void SphereCollider::DrawDebug(AWindow* window)
{
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

void SphereCollider::DrawSDL(WindowSDL* windowSDL)
{
    SDL_Renderer* renderer = windowSDL->GetRenderer();
    if (!renderer) return; // Vérifiez que le renderer est valide

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);

    int centerX = static_cast<int>(m_position.GetX());
    int centerY = static_cast<int>(m_position.GetY());
    int radius = m_radius;

    for (int w = -radius; w <= radius; ++w) 
    {
        for (int h = -radius; h <= radius; ++h) 
        {
            if ((w * w + h * h) <= (radius * radius))
            {
                SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

void SphereCollider::DrawRaylib()
{
    // Définir la couleur pour le cercle (rouge semi-transparent)
    Color debugColor = { 255, 0, 0, 128 }; // Rouge avec alpha (transparence)

    // Dessiner un cercle rempli
    DrawCircle(m_position.GetX(), m_position.GetY(), m_radius, debugColor);
}
