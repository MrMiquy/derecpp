#include <SDL2/SDL.h>
#include <functional>

#ifndef WIDGET
#define WIDGET

enum MouseState {
    mouseNone,
    mouseHover,
    mousePressed,
};

class Colorize {
public:
    Colorize();
    ~Colorize();

    void setColor(SDL_Color color);
    SDL_Color getColor();
    void setHoverColor(SDL_Color color);
    SDL_Color getHoverColor();
    void setPressedColor(SDL_Color color);
    SDL_Color getPressedColor();
    void setAlpha(Uint8 value);
    Uint8 getAlpha();
    void setHoverAlpha(Uint8 value);
    Uint8 getHoverAlpha();
    void setPressedAlpha(Uint8 value);
    Uint8 getPressedAlpha();

    SDL_Color* colorReference();

    void Colorizing(bool value) {useColorize = value;}
    SDL_Color getColorByState(MouseState ms);

protected:
    bool useColorize = true;
    SDL_Color color = {0, 0, 0, 255};
    SDL_Color hoverColor = {20, 20, 20, 255};
    SDL_Color pressedColor = {30, 30, 30, 255};
};

class Widget {
public:
    Widget();
    ~Widget();

    virtual void setRenderer(SDL_Renderer* renderer);
    void setEnable(bool isEnable);
    void setDraggable(bool value);
    void setMouseState(MouseState state);
    virtual void setGeometry(SDL_Rect geometry);
    void bindHoverFunction(std::function<void()> function);
    void bindPressedFunction(std::function<void()> function);

    MouseState getMouseState();
    SDL_Rect getGeometry();
    bool isEnable();
    bool isDraggable();
    SDL_Rect* geometryReference();
    int* xReference();
    int* yReference();
    int* widthReference();
    int* heightReference();

    bool hover(int x, int y);                                 // is mouse over
    bool pressed(int x, int y, bool press = true);                              // is mouse pressed
    bool collisse(int x, int y);
    void invertEnable();

    virtual void render();

    MouseState ms = mouseNone;

protected:
    SDL_Rect geometry = {0, 0, 0, 0};
    SDL_Renderer* renderer;
    bool enable = true;
    bool drag = false;

    void addX(int value);
    void addY(int value);
    void addW(int value);
    void addH(int value);
    void addNormalized(int value);

    std::function<void()> hoverFunc;
    std::function<void()> pressedFunc;
};

#endif
