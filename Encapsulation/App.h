#pragma once
class AWindow;
class ASprite;

class App
{
public:
	void Run();

private:
	AWindow* m_window;
	ASprite* m_sprite;
	void Update();
};

