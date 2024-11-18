#pragma once

namespace Maths 
{
	class Vector2
	{
	private:
		int m_x;
		int m_y;

	public:
		Vector2();
		Vector2(int x, int y);
		int GetX();
		void SetX(int x);
		int GetY();
		void SetY(int y);
	};
}

