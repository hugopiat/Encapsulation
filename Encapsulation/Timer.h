#pragma once
const int FPS_MAX = 100;
const int FPS_MIN = 10;

class Timer
{

protected:
	bool m_haveToResetDeltaTime;
	long long m_lastTick;
	static float m_deltaTime;
public:
	static float GetDeltaTime();
	bool UpdateTime();
};

