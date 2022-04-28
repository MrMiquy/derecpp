#include "App.h"

App* app = nullptr;

const unsigned short frameDelay = 30;

int main(int argc, char** argv)
{
    app = new App("test UI", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 805, 500, SDL_WINDOW_RESIZABLE);

    Uint32 frameStart;
    int frameTime;

    try {
        while(app->isRunning()) {

            frameStart = SDL_GetTicks();

            app->handleEvents();
            app->update();

            if (app->animation())
                app->render();

            app->frame++;

            if (app->frame > 99)
                app->frame = 0;


            frameTime = SDL_GetTicks() - frameStart;
            if (frameDelay > frameTime) SDL_Delay(frameDelay - frameTime);
        }
    } catch (std::exception *e) {
        printf("error: %s\n", e->what());
    }

    app->clean();

    delete app;
    return 0;
}

