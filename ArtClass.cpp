#include "ArtClass.h"

ArtClass::ArtClass(SDL_Renderer* _renderer, const char* filename) {
        renderer = _renderer;
        texture = loadTexture(filename);
        SDL_QueryTexture(texture, NULL, NULL, &geometry.w, &geometry.h);
}

ArtClass::~ArtClass() {
    SDL_DestroyTexture(texture);
}

void ArtClass::setPos(int x, int y) {
    geometry.x = x;
    geometry.y = y;
}

void ArtClass::render() {
    SDL_RenderCopy(renderer, texture, NULL, &geometry);
}

void ArtClass::setIID(unsigned int _IID) {
    IID = _IID;
}

SDL_Texture* ArtClass::loadTexture(const char* filename) {
    SDL_Surface* tempSurface = IMG_Load(filename);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}
