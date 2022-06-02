#include "Widget.h"
#include <string>
#include <SDL2/SDL_ttf.h>

class Label : public Widget, public Colorize {
public:
    Label();
    ~Label();

    void setRenderer(SDL_Renderer* renderer);
    void setText(std::string text);
    void setFont(std::string fontname, int fontsize);

    std::string getText();

    void render();

protected:
    std::string text;
    TTF_Font* font = NULL;
    SDL_Texture* texture = NULL;

    void applyTexture();
    void updateDock();

};
