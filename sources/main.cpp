#include "../headers/App.h"

void runApp() {
    App app;

    app.init("Yande.re", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 805, 500, SDL_WINDOW_RESIZABLE);

    while (app.isRunning()) {
        app.cycle();
    }
}

int main(int argc, char** argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();
    IMG_Init(0);

    runApp();

    TTF_Quit();
    IMG_Quit();
    SDL_Quit();

    return 0;
}

