#pragma once
#include "Vector2.h"
#include <functional>

class ASprite;
class Collider;
class BoxCollider;

class Brick
{
private:

    ASprite* m_sprite;
    BoxCollider* m_boxCollider;
    Maths::Vector2 m_pos;

public:

    bool m_enabledLife;
    int m_life;
    bool m_isDie;

    Brick();
    void Destroy();

    void Init(const Maths::Vector2 pos, ASprite* sprite, float width = 50, float height = 50);
    void SetPosition(const Maths::Vector2 pos);
    Maths::Vector2 GetPosition();
    void Update(float deltaTime);
    void Draw();

    void OnCollisionEnter(Collider& other);
    Collider* GetCollider();
};

