#pragma once
#include <vector>
#include <iostream>
#include "AInputSystem.h"
class AWindow;
class ASprite;
class AText;
class AInputSystem;
class Timer;
class Wall;
class Ball;
class Brick;
class Player;
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

	const std::string m_filenameBall = "Basketball.png";
	const std::string m_filenameWall = "Wall.png";
	void Run(int argc, char* argv[]);
	static GraphicLib GetGraphicLibType();

	float m_cooldownSpawn = 0.5f;
	float m_currentCooldown = 0.0f;

private:
	AWindow* m_window;
	ASprite* m_spriteBall;
	ASprite* m_spriteWall;
	AText* m_text;
	Encapsulation::AInputSystem* m_inputSystemInstance;
	Timer* m_timer;
	ColliderManager* m_managerCollider;
	std::vector<Wall*> m_walls;
	std::vector<Ball*> m_balls;
	std::vector<Brick*> m_bricks;

	Player* m_player;

	static GraphicLib m_graphicLibType;

	int m_inputLeft;
	int m_inputRight;
	
	bool ManageArgs(int argc, char* argv[]);
	bool PerformArgForGraphicLib(const std::string& arg);
	void Init();
	void Draw();
	void Update(float deltaTime);

	void SpawnPlayer();
	void SpawnBallsNearPlayer(int count);
	void SpawnBalls(int count);
	void SpawnBrick(int count);

	void InputUpdate();

	void DeleteBalls();
	void DeleteBricks();
};

