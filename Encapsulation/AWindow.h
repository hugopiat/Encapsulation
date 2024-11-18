#pragma once
class AWindow
{
public:
	int m_width = 1280;
	int m_height = 720;

	virtual void Init() = 0;
	virtual void Draw() = 0;
	virtual void Clear() = 0;
	virtual bool IsOpen() = 0;
	virtual bool Close() = 0;

};

