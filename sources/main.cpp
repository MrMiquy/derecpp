#include "../headers/App.h"

App* app = nullptr;

const unsigned short frameDelay = 10;

int main(int argc, char** argv)
{
    App app("Yande.re", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 805, 500, SDL_WINDOW_RESIZABLE);

    Uint32 frameStart;
    int frameTime;

    while(app.isRunning()) {
        frameStart = SDL_GetTicks();

        app.handleEvents();
        app.update();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime)
            SDL_Delay(frameDelay - frameTime);
    }

    app.clean();
    return 0;
}

