#include "InputSystemRaylib.h"
#include "raylib.h"
void InputSystemRaylib::PoolEvent()
{
	for (int i = 0; i < s_keys.size() ; i++)
	{
		if (IsKeyPressed(i))
		{
			s_keys[i] = KeyState::KeyPressed;
		}
		else if (IsKeyDown(i))
		{
			s_keys[i] = KeyState::KeyDown;
		}
		else if (IsKeyReleased(i))
		{
			s_keys[i] = KeyState::KeyReleased;
		}
		else if (IsKeyUp(i))
		{
			s_keys[i] = KeyState::KeyUp;
		}
	}
}
