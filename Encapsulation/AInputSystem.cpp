#include "AInputSystem.h"
using namespace Encapsulation;

std::vector<KeyState> AInputSystem::s_keys = std::vector<KeyState>();
bool AInputSystem::IsInputKeyPressed(int code)
{
    return s_keys[code] == KeyState::KeyPressed;
}

bool AInputSystem::IsInputKeyDown(int code)
{
    return s_keys[code] == KeyState::KeyDown;
}

bool AInputSystem::IsInputKeyReleased(int code)
{
    return s_keys[code] == KeyState::KeyReleased;
}

bool AInputSystem::IsInputKeyUp(int code)
{
    return s_keys[code] == KeyState::KeyUp;
}

void AInputSystem::Init()
{
    for (int i = 0; i < 255; i++)
    {
        s_keys.push_back(KeyState::None);
    }
}
