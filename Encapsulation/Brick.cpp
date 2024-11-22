#include "Brick.h"

#include "ASprite.h"
#include "Ball.h"

#include "BoxCollider.h"

using namespace std::placeholders;

Brick::Brick() :
    m_sprite(nullptr),
    m_boxCollider(nullptr),
    m_pos(0, 0),
    m_life(0),
    m_isDie(false),
    m_enabledLife(false)
{

}

void Brick::Destroy()
{
    if (m_boxCollider != nullptr) {
        delete m_boxCollider; 
        m_boxCollider = nullptr;
    }
}

void Brick::Init(const Maths::Vector2 pos, ASprite* sprite, float width, float height)
{
    m_sprite = sprite;
    m_life = 2;
    m_enabledLife = true;

    m_boxCollider = new BoxCollider(pos, width, height);
    m_boxCollider->SetOwner(this);

    m_boxCollider->m_collisionType = CollisionType::Brick;
    //m_boxCollider->AddCollisionTypeTarget(CollisionType::Ball);
    m_boxCollider->SetOnCollisionEnterCallback(std::bind(&Brick::OnCollisionEnter, this, _1));
    SetPosition(pos);
}

void Brick::SetPosition(const Maths::Vector2 pos)
{
    m_pos = pos;
    m_boxCollider->SetPosition(m_pos);
    m_sprite->SetPositionSprite(m_pos);
}

Maths::Vector2 Brick::GetPosition()
{
    return m_pos;
}

void Brick::Update(float deltaTime)
{

}

void Brick::Draw()
{
    m_sprite->Draw();
}

void Brick::OnCollisionEnter(Collider& other)
{
    Ball* ball = static_cast<Ball*>(other.GetOwner()); // Récupérer le propriétaire de `SphereCollider`

    if (ball != nullptr && m_enabledLife)
    {
        // Réduire la vie de la brique en fonction des dégâts de la balle
        m_life -= ball->m_damage;

        if (m_life <= 0)
        {
            m_isDie = true;
        }
    }
}

Collider* Brick::GetCollider()
{
	return m_boxCollider;
}
