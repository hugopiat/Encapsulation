#pragma once

class Vector2
{
public :
	int m_x;
	int m_y; 

	Vector2();
	Vector2(int x, int y);
	int GetPositionX();
	void SetPositionX(int x);
	int GetPositionY();
	void SetPositionY(int y);
};

