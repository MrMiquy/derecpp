#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

class ArtClass {
public:
    SDL_Rect geometry = {0, 0, 0, 0};
    unsigned int IID = 0;

    ArtClass(SDL_Renderer* _renderer, const char* filename);

    SDL_Texture* getTexture() { return texture; }
    ~ArtClass();

    void setIID(unsigned int _IID);
    void setPos(int x, int y);
    void render();

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    SDL_Texture* loadTexture(const char* filename);
};
