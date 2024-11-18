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

		void CopyVector2(Vector2& vect2Origin);

		int GetX();
		int GetY();

		void SetX(int x);
		void SetY(int y);
	};
}

