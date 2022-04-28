#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <thread>
#include "yandere.h"
#include "UI.h"

class App : public UI {
public:
    App(const char* title, int xPos, int yPos, int width, int height, uint resizable);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

    void makeTags();
    void makeArts();

private:
    int mouseX, mouseY;
    int cnt = 0;
    int xO, yO = 0;
    bool run = false;
    bool neededRender = false;
    bool isMakingTags = false;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;

    Parser parser;
};
