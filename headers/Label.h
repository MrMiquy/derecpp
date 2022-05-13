#include "Widget.h"
#include <string>
#include <SDL2/SDL_ttf.h>

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

class Label : public Widget, public Colorize {
public:
    Label();
    ~Label();

    void setText(std::string text);
    void setDock(Dock dock);
    void addMargin(SDL_Rect margin);
    void setFont(std::string fontname, int fontsize);

    std::string getText();
    Dock getDock();
    SDL_Rect getMargin();

protected:
    std::string text;
    SDL_Rect margin;
    Dock dock;
    TTF_Font* font;
    SDL_Texture* texture;

};
