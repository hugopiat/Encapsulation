#include "SphereCollider.h"

#include <SDL2/SDL.h>
#include <cmath>

#include "AWindow.h"
#include "WindowSDL.h"
#include "WindowRaylib.h"
#include "BoxCollider.h"
#include <raylib.h>

SphereCollider::SphereCollider(Maths::Vector2 position, float radius, Maths::Vector2 velocity) :
    m_radius(radius)
{
    SetColliderPos(position);
    SetVelocity(velocity);
}

int SphereCollider::GetRadius() const
{
    return m_radius;
}

bool SphereCollider::CheckCollision(const Collider* other) const
{
    if (const SphereCollider* sphere = dynamic_cast<const SphereCollider*>(other)) {
        // Calculer la distance entre les centres des deux sphères
        float dx = GetPosition().GetX() - sphere->GetPosition().GetX();
        float dy = GetPosition().GetY() - sphere->GetPosition().GetY();
        float distance = std::sqrt(dx * dx + dy * dy);
        return distance < (m_radius + sphere->m_radius);
    }
    else if (const BoxCollider* box = dynamic_cast<const BoxCollider*>(other)) {
        // Si c'est un BoxCollider, tu peux gérer la collision avec un rectangle ici.
        return box->CheckCollision(this);  // Appel au BoxCollider pour vérifier
    }
    return false;
}

Maths::Vector2 SphereCollider::GetPosition() const
{
	return m_position;
}

void SphereCollider::SetColliderPos(const Maths::Vector2 newPos)
{
    m_position = newPos;
}

Maths::Vector2 SphereCollider::GetVelocity() const
{
    return m_velocity;
}

void SphereCollider::SetVelocity(const Maths::Vector2 newVelocity)
{
    m_velocity = newVelocity;
}

void SphereCollider::DrawDebug(AWindow* window)
{
    WindowSDL* windowSDL = dynamic_cast<WindowSDL*>(window);
    if (windowSDL)
    {
        SDL_Renderer* renderer = windowSDL->GetRenderer();
        if (!renderer) return; // Vérifiez que le renderer est valide

        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 128);

        int centerX = static_cast<int>(m_position.GetX());
        int centerY = static_cast<int>(m_position.GetY());
        int radius = m_radius;

        for (int w = -radius; w <= radius; ++w) {
            for (int h = -radius; h <= radius; ++h) {
                if ((w * w + h * h) <= (radius * radius)) {
                    SDL_RenderDrawPoint(renderer, centerX + w, centerY + h);
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    }

    WindowRaylib* windowRAYLIB = dynamic_cast<WindowRaylib*>(window);
    if (windowRAYLIB)
    {
        // Définir la couleur pour le cercle (rouge semi-transparent)
        Color debugColor = { 255, 0, 0, 128 }; // Rouge avec alpha (transparence)

        // Récupérer les coordonnées du centre du cercle et son rayon
        float centerX = m_position.GetX(); // Coordonnée X du centre
        float centerY = m_position.GetY(); // Coordonnée Y du centre
        float radius = m_radius;           // Rayon du cercle

        // Dessiner un cercle rempli
        DrawCircle(centerX, centerY, radius, debugColor);

        // Dessiner le contour du cercle
        //DrawCircleLines(centerX, centerY, radius, debugColor);
    }
}
