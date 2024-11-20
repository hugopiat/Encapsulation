#pragma once

namespace Maths
{
	class Utils
	{
    public:

        template <typename T>
        static T Clamp(T value, T min, T max);

        template <typename T>
        static T ABS(T value);
	};

    template <typename T>
    static T Utils::Clamp(T value, T min, T max)
    {
        if (value < min)
        {
            return min;
        }
        else if (value > max)
        {
            return max;
        }
        else
        {
            return value;
        }
    }

    template <typename T>
    static T Utils::ABS(T value)
    {
        return value < 0 ? -value : value; // On peut aussi utiliser std::abs(T value) pour plus de flexibilité
    }
}

