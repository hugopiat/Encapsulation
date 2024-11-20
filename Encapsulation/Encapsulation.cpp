#include <iostream>
#include <string>
#include "App.h"
int main(int argc, char* argv[])
{
    
    App* app = new App();
    app->Run(argc, argv);
    return 0;

}
