#pragma once
#include <vector>

enum class KeyState
{
	None = 0,
	KeyPressed = 1,
	KeyDown = 2,
	KeyReleased = 3,
	KeyUp = 4
};
namespace Encapsulation 
{
	class AInputSystem
	{
	protected:
		static std::vector<KeyState> s_keys;
	public:
		static bool IsInputKeyPressed(int code);
		static bool IsInputKeyDown(int code);
		static bool IsInputKeyReleased(int code);
		static bool IsInputKeyUp(int code);

		static void Init();
		virtual void PoolEvent() = 0;
	};
}


