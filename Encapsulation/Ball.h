#pragma once
#include "Vector2.h"

class ASprite;
class Collider;
class SphereCollider;

class Ball
{
private:

    ASprite* m_sprite;
    SphereCollider* m_sphereCollider;
    Maths::Vector2 m_pos;
    Maths::Vector2 m_direction;
    float m_speed;

    Maths::Vector2 InitNextPos(float deltaTime);
    bool CheckCollisionBounds(Maths::Vector2 nextPos, int windowWidth, int windowHeight);

public:

    Ball();

    void Init(const Maths::Vector2 pos, const Maths::Vector2 direction, ASprite* sprite, float radius = 50);
    void SetSpeed(float speed);
    void Update(float deltaTime, int windowWidth, int windowHeight);
    void Draw();

    Collider* GetCollider();
};

