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
    m_isDie(false)
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
    m_pos = pos;
    m_sprite = sprite;
    m_life = 3;

    m_boxCollider = new BoxCollider(pos, width, height);
    m_boxCollider->SetOwner(this);

    m_boxCollider->m_collisionType = CollisionType::Brick;
    m_boxCollider->AddCollisionTypeTarget(CollisionType::Ball);
    m_boxCollider->SetOnCollisionEnterCallback(std::bind(&Brick::OnCollisionEnter, this, _1));
}

void Brick::Update(float deltaTime)
{
}

void Brick::Draw()
{
    m_sprite->SetPositionSprite(m_pos);
    m_sprite->Draw();
}

void Brick::OnCollisionEnter(Collider& other)
{
    Ball* ball = static_cast<Ball*>(other.GetOwner()); // Récupérer le propriétaire de `SphereCollider`

    if (ball != nullptr)
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
