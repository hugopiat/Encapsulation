#include <iostream>

int main()
{
#if _RAYLIB
    std::cout << "Hello World Raylib!\n";
#endif  // _RAYLIB
#if _SDL 
    std::cout << "Hello World SDL!\n";
#endif // _SDL
}