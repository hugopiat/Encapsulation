#pragma once
const int FPS_MAX = 60;

class Timer
{

protected:
	bool m_haveToResetDeltaTime;
	unsigned int m_lastTick;
	static float m_deltaTime;
public:
	static float GetDeltaTime();
	bool UpdateTime();
};
