#include <iostream>
#include "App.h"
int main(int argc, char* argv[])
{
#if _RAYLIB
    std::cout << "Hello World Raylib!\n";
#endif  // _RAYLIB
#if _SDL 
    std::cout << "Hello World SDL!\n";
#endif // _SDL
    //const char* arg1 = argv[1];
    //bool test = arg1 == "sdl";
    //for (int i = 0; i < argc; i++)
    //{
    //    std::cout << argv[i] << std::endl;
    //    std::cout << test << std::endl;
    //}

    //return 0;
    App* app = new App();
    app->Run();
    return 0;

}
