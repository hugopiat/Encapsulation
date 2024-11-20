#pragma once
#include <vector>
#include <iostream>

class AWindow;
class ASprite;
class Timer;
class Ball;
class ColliderManager;


enum class GraphicLib
{
	NONE = 0,
	RAYLIB = 1,
	SDL2 = 2
};

class App
{
public:
	const std::string filename = "Basketball.png";
	void Run(int argc, char* argv[]);

private:
	AWindow* m_window;
	ASprite* m_sprite;
	GraphicLib m_graphicLibType;
	Timer* m_timer;
	ColliderManager* m_managerCollider;
	std::vector<Ball*> balls;

	
	bool ManageArgs(int argc, char* argv[]);
	bool PerformArgForGraphicLib(const std::string& arg);
	void Init();
	void Draw();
	void Update(float deltaTime);
	void SpawnBalls(int count);
	void DeleteBalls();
};

