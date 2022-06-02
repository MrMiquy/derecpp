#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "Widget.h"
#include <string>

class Image : public Widget {
public:
    Image();
    ~Image();

    void setImage(std::string filename);

    SDL_Texture* getTexture();

    void setRenderer(SDL_Renderer* renderer);
    void render();

protected:
    SDL_Texture* texture = NULL;

    SDL_Texture* loadTexture();

private:
    std::string filename;
};
