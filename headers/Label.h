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

    void setGeometry(SDL_Rect geometry);
    void setRenderer(SDL_Renderer* renderer);
    void setText(std::string text);
    void setDock(Dock dock);
    void setFont(std::string fontname, int fontsize);

    std::string getText();
    Dock getDock();
    SDL_Rect getMargin();

    void addMargin(SDL_Rect margin);

    void render();

protected:
    SDL_Rect nativeGeometry;
    std::string text;
    SDL_Rect margin;
    Dock dock;
    TTF_Font* font = NULL;
    SDL_Texture* texture = NULL;

    void applyTexture();
    void updateDock();

};
