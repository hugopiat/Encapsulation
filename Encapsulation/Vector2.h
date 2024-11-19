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

        Vector2& operator+=(const Vector2& other) {
            m_x += other.m_x;
            m_y += other.m_y;
            return *this;
        }

        Vector2& operator-=(const Vector2& other) {
            m_x -= other.m_x;
            m_y -= other.m_y;
            return *this;
        }

        bool operator==(const Vector2& other) const {
            return m_x == other.m_x && m_y == other.m_y;
        }

        bool operator!=(const Vector2& other) const {
            return !(*this == other);
        }
	};
}

