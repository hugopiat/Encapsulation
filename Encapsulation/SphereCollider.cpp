#include "SphereCollider.h"

#include <SDL2/SDL.h>
#include <cmath>

#include "AWindow.h"
#include "WindowSDL.h"
#include "WindowRaylib.h"
#include "BoxCollider.h"
#include <raylib.h>

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
        // Calculer la distance entre les centres des deux sphères
        float dx = GetPosition().GetX() - sphere->GetPosition().GetX();
        float dy = GetPosition().GetY() - sphere->GetPosition().GetY();

        float distanceSquared = dx * dx + dy * dy;
        float combinedRadius = m_radius + sphere->m_radius;

        if (distanceSquared < (combinedRadius * combinedRadius))
        {
            Maths::Vector2 direction = Maths::Vector2(dx, dy);
            Maths::Vector2 directionOther = Maths::Vector2(-dx, -dy);

            direction.Normalize();
            directionOther.Normalize();

            SetNormal(direction);
            sphere->SetNormal(directionOther);

            return true;
        }
        return false;
    }
    else if (BoxCollider* box = dynamic_cast<BoxCollider*>(other)) 
    {
        return box->CheckCollision(this);
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
