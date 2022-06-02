#include <SDL2/SDL.h>
#include <functional>

#ifndef __WIDGET
#define __WIDGET

enum MouseState {
    mouseNone,
    mouseHover,
    mousePressed,
};

enum Dock {
    NoneDock,
    TopDock,
    LeftDock,
    BottomDock,
    RightDock,

    CenterDock,

    TopLeftDock,
    TopRightDock,

    BottomLeftDock,
    BottomRightDock
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

    void setAutoColorizing(bool value) {useColorize = value;}
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

    // UI
    virtual void setRenderer(SDL_Renderer* renderer);
    void setEnable(bool isEnable);
    void setDraggable(bool value);
    void setMouseState(MouseState state);

    MouseState getMouseState();
    SDL_Rect getGeometry();
    bool isEnable();
    bool isDraggable();
    bool isHover() { return isHoverNow; }

    // LOCATION
    virtual void setGeometry(SDL_Rect geometry);
    virtual void setNativeGeometry(SDL_Rect geometry);
    virtual void setDockGeometry(SDL_Rect dockGeometry);
    virtual void setPos(SDL_Point pos);
    virtual void setSize(SDL_Point size);

    virtual void setMargin(SDL_Rect margin);
    virtual void setPadding(SDL_Rect padding);
    void setDock(Dock dock, int margin = 0);
    void updateDock();

    virtual void proportionalSizeW(float width);
    virtual void proportionalSizeH(float height);

    SDL_Point getMargin();
    SDL_Rect getPadding();
    SDL_Rect* geometryReference();
    int* xReference();
    int* yReference();
    int* widthReference();
    int* heightReference();

    // LOGIC
    void bindHoverFunction(std::function<void()> function);
    void bindUnhoverFunction(std::function<void()> function);
    void bindPressedFunction(std::function<void()> function);
    void bindUnpressedFunction(std::function<void()> function);
    void bindScrollUpFunction(std::function<void()> function);
    void bindScrollDownFunction(std::function<void()> function);
    void bindWinResizeFunction(std::function<void()> function);

    bool hover(int x, int y);                             // is mouse over
    bool pressed(int x, int y, bool press = true);       // is mouse pressed
    bool collisse(int x, int y);
    void invertEnable();
    virtual void scrollUp();
    virtual void scrollDown();
    virtual void winResize();

    virtual void render();

protected:
    Dock dock;
    SDL_Point margin = {0, 0};
    SDL_Rect padding = {0, 0, 0, 0};
    SDL_Rect geometry = {0, 0, 0, 0};
    SDL_Rect dockGeometry = {0, 0, 0, 0};
    SDL_Rect nativeGeometry = {0, 0, 0, 0};
    MouseState ms = mouseNone;
    SDL_Renderer* renderer;
    bool enable = true;
    bool drag = false;
    bool isHoverNow = false;

    void addX(int value);
    void addY(int value);
    void addW(int value);
    void addH(int value);
    void addNormalized(int value);

    std::function<void()> hoverFunc;
    std::function<void()> unhoverFunc;
    std::function<void()> pressedFunc;
    std::function<void()> unpressedFunc;
    std::function<void()> scrollUpFunc;
    std::function<void()> scrollDownFunc;
    std::function<void()> winResizeFunc;
};

#endif // __WIDGET
