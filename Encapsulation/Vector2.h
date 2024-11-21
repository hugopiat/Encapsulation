#pragma once

namespace Maths 
{
	class Vector2
	{
	private:
        float m_x;
        float m_y;

	public:

		Vector2();
		Vector2(float x, float y);

        void Normalize();
        static float Scalar(const Vector2& origin, const Vector2& second);

		float GetX() const;
        float GetY() const;

		void SetX(float x);
		void SetY(float y);

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
            return m_x != other.m_x || m_y != other.m_y;
        }

        Vector2 operator+(const Vector2& other) const {
            return Vector2(m_x + other.m_x, m_y + other.m_y);
        }

        Vector2 operator-(const Vector2& other) const {
            return Vector2(m_x - other.m_x, m_y - other.m_y);
        }

        Vector2 operator*(int scalar) const {
            return Vector2(m_x * scalar, m_y * scalar);
        }

        Vector2 operator/(int scalar) const {
            return Vector2(m_x / scalar, m_y / scalar);
        }
	};
}

