#pragma once
#include "Vector2.h"

class ASprite;

class Ball
{
public:

    Ball();

    void Init(Maths::Vector2 pos, Maths::Vector2 speed, ASprite* sprite);
    void Update(float deltaTime, int windowWidth, int windowHeight);
    void Draw();

    int ABS(int value);

private:

    Maths::Vector2 m_pos;
    Maths::Vector2 m_speed;
    ASprite* m_sprite;
};

