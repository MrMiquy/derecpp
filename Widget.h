#ifndef __WIDGET__
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <functional>

#include "SDL2/SDL_ttf.h"

enum EditState {
    Completed,
    Editing
};

enum ButtonState {
    Default,
    MouseOver,
    Pressed
};

enum Dock {
    NoneDock,
    Top,
    Left,
    Bottom,
    Right,

    Center,

    TopLeft,
    TopRight,
    BottomRight,
    BottomLeft
};

struct Margin {
    int left, top, right, bottom;
};

class Widget {
public:
    SDL_Renderer* renderer;
    SDL_Rect geometry = {0, 0, 0, 0};

    void setRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }
    virtual void render() { }
    void setEnable(bool value) { isEnable = value; }
    bool getEnable() { return isEnable; }
    void invertEnable();

private:
    bool isEnable = true;
};

class Text : public Widget {
public:
    Margin margin = {0, 0, 0, 0};
    Margin offset_margin = {0, 0, 0, 0};
    SDL_Rect renderingGeometry;
    TTF_Font* font;
    SDL_Texture* texture;
    SDL_Color color = {255, 255, 255, 255};
    Dock dock = NoneDock;

    int textWidth, textHeight;
    std::string text;

    Text();
    Text(SDL_Renderer* _renderer, std::string _text, const char* fontname, int size, SDL_Rect _geometry);
    virtual ~Text();

    void setAlpha(Uint8 _alpha);
    void setFont(const char* fontFilename, int fontSize);
    void setColor(SDL_Color _color);
    void setText(const char* _text);
    void setRenderer(SDL_Renderer* renderer);
    void setTexture();
    void setMargin(int _left = 0, int _top = 0, int _right = 0, int _bottom = 0);

    void setDock(Dock dock, int marginDock = 0, bool forcibly = false);
    void updateDock();

    void render() override;

private:
    Uint8 alpha = 100;
};

class Plate : public Widget {
public:
    SDL_Color color;

    Plate();
    Plate(SDL_Renderer* _renderer, SDL_Rect _geometry = {0, 0, 0, 0}, SDL_Color _color = {0, 0, 0, 0});
    virtual ~Plate();
    void render();
    void addChild(Widget* child);

    std::vector<Widget*> children;
};

class EditBox {
public:
    EditState state = Completed;
    Text text;
    Text hint;
    Plate plate;
    int line_offset = 0;

    bool isBindText = true;
    bool isRenderLine = false;

    EditBox(SDL_Renderer* renderer, SDL_Rect _geometry = {0, 0, 10, 10}, SDL_Color background = {0, 0, 0, 0}, SDL_Color foreground = {255, 255, 255, 255});
    ~EditBox();

    bool isMouseOn(int x, int y);

    bool edit();
    bool complete();

    void setEditColor(SDL_Color background = {0, 0, 0, 0}, SDL_Color foreground = {0, 0, 0, 0});
    void setCompleteColor(SDL_Color background = {0, 0, 0, 0}, SDL_Color foreground = {0, 0, 0, 0});

    void bindText();
    bool renderLine(int frame);
    void render();

private:
    SDL_Color editBgColor = {0, 0, 0, 0};
    SDL_Color editFgColor = {0, 0, 0, 0};
    SDL_Color completeBgColor = {0, 0, 0, 0};
    SDL_Color completeFgColor = {0, 0, 0, 0};
};

class Button : public Plate {
public:
    Text text;
    ButtonState state;
    bool isBindText = true;

    Button(SDL_Renderer* _renderer, const char* _text, SDL_Rect _geometry, SDL_Color _color, bool useAutoAdvColors = true, bool textMargin = true);
    ~Button();

    bool isMouseOn(int x, int y);
    bool isPressed(int x, int y);

    void setColor(SDL_Color _color);
    void setAdvColors(SDL_Color MouseOverColor, SDL_Color pressColor);
    void lostPressedFocus(int x, int y);
    void setGeometry(SDL_Rect _geometry);
    void bindText(bool isBinded);

    void bindSignal(std::function<void()> func);
    void render();

private:
    std::function<void()> pressedPtr;
    SDL_Color defColor = {200, 200, 200, 55};
    SDL_Color mouseOverColor;
    SDL_Color pressColor;
};



#define __WIDGET__
#endif // WIDGET
