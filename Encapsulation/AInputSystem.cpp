#include "AInputSystem.h"
using namespace Encapsulation;

std::vector<KeyState> AInputSystem::s_keys = std::vector<KeyState>();
bool Encapsulation::AInputSystem::IsInputAnyKeyPressed()
{
    for (const auto& keyState : s_keys)
    {
        if (keyState == KeyState::KeyPressed)
        {
            return true; // Une touche est pressée
        }
    }

    return false; // Aucune touche pressée
}
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
