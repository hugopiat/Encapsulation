#pragma once
#include <vector>
#include "iostream"

class AWindow;
class ASprite;
class ATimer;
class Ball;

class App
{
public:
	const std::string filename = "Basketball.png";
	void Run();

private:
	AWindow* m_window;
	ASprite* m_sprite;
	ATimer* m_timer;
	std::vector<Ball*> balls;

	void Draw();
	void Update(float deltaTime);
	void SpawnBalls(int count);
	void DeleteBalls();
};

