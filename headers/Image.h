#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Widget.h"
#include <string>

class Image : public Widget {
public:
    Image();
    ~Image();

    void setImage(std::string filename);
    void setPosition(SDL_Point position);
    void setSize(SDL_Point size);

    SDL_Texture* getTexture();
    SDL_Point getPosition();
    SDL_Point getSize();

    void setRenderer(SDL_Renderer* renderer);
    void render();

protected:
    SDL_Texture* texture = NULL;

    SDL_Texture* loadTexture();

private:
    std::string filename;
};
