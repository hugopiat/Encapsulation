#pragma once
#include <vector>

class AWindow;
class ASprite;
class Ball;

class App
{
public:
	void Run();

private:
	AWindow* m_window;
	ASprite* m_sprite;
	std::vector<Ball*> balls;
	void Draw();
	void Update(float deltaTime);
	void SpawnBalls(int count);
};

