#pragma once
#include <vector>
#include <iostream>

class AWindow;
class ASprite;
class AText;
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

	static GraphicLib GetGraphicLibType();

private:
	AWindow* m_window;
	ASprite* m_sprite;
	AText* m_text;
	Timer* m_timer;
	ColliderManager* m_managerCollider;
	std::vector<Ball*> balls;

	static GraphicLib m_graphicLibType;
	
	bool ManageArgs(int argc, char* argv[]);
	bool PerformArgForGraphicLib(const std::string& arg);
	void Init();
	void Draw();
	void Update(float deltaTime);
	void SpawnBalls(int count);
	void DeleteBalls();
};

