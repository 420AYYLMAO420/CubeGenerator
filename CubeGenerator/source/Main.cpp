#include "App.h"

int main() {

    //create instance of window
    App* app = new App("Cube Generator", 1280, 720);
    if (app != nullptr)
        app->Run();
    else
        return -1;

    delete app;
    return 0;
    
}