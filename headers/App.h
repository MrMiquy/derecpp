#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include <functional>
#include "MainWindow.h"

template <typename T> std::vector<T> concat(std::vector<T> &a, std::vector<T> &b) {
    std::vector<T> ret = std::vector<T>();
    std::copy(a.begin(), a.end(), back_inserter(ret));
    std::copy(b.begin(), b.end(), back_inserter(ret));
    return ret;
}

class App : public MainWindow {
public:
    App();
    ~App();

    void cycle();
    void handleEvents();
    void update();
    void render();

    SDL_Point getWindowSize();
    SDL_Point getWindowPos();

private:
    int mouseX, mouseY;
    int mouseXo, mouseYo;
    bool mouseUp = false;
    bool mouseDown = false;
    bool neededRender = false;
    bool mouse = false;
    bool mouseChanged = false;
    int skipFrame = 0;
    int motions = 0;
    const unsigned short frameDelay = 10;
    unsigned int frameStart;
    int frameTime;

    Widget* lastPressedWidget = NULL;
};
