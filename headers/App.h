#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include "UI.h"

template <typename T> std::vector<T> concat(std::vector<T> &a, std::vector<T> &b) {
    std::vector<T> ret = std::vector<T>();
    std::copy(a.begin(), a.end(), back_inserter(ret));
    std::copy(b.begin(), b.end(), back_inserter(ret));
    return ret;
}

class App : protected UI {
public:
    App(const char* title, int xPos, int yPos, int width, int height, uint resizable);

    void handleEvents();
    void update();
    void render();
    void clean();
    bool isRunning();

    SDL_Point getWindowSize();
    SDL_Point getWindowPos();

private:
    int mouseX, mouseY;
    int mouseXo, mouseYo;
    bool run = false;
    bool neededRender = false;
    bool mouse = false;
    bool mouseChanged = false;
    int skipFrame = 0;
    int motions = 0;

    SDL_Point winSize = {0, 0};
    SDL_Point winPos = {0, 0};
    SDL_Window* window;
    SDL_Surface* surface;

    Widget* lastPressedWidget = NULL;
};
