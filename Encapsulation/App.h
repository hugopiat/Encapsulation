#pragma once
class AWindow;

class App
{
public:
	void Run();

private:
	AWindow* m_window;
	void Update();
};

