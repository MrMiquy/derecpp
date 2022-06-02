#include "../headers/Image.h"

Image::Image() {
}

Image::~Image() {
    SDL_DestroyTexture(texture);
}

void Image::setImage(std::string _filename) {
    if (filename != "") {
        filename = _filename;
        texture = loadTexture();
        SDL_QueryTexture(texture, NULL, NULL, &geometry.w, &geometry.h);    // Get texture's (image's) size;
    } else {
        filename = _filename;
    }
}

void Image::setRenderer(SDL_Renderer* _renderer) {
    Widget::setRenderer(_renderer);

    texture = loadTexture();
    SDL_QueryTexture(texture, NULL, NULL, &geometry.w, &geometry.h);    // Get texture's (image's) size;
    nativeGeometry.w = geometry.w;
    nativeGeometry.h = geometry.h;
}

void Image::render() {
    SDL_RenderCopy(renderer, texture, NULL, &geometry);
}

SDL_Texture* Image::loadTexture() {
    SDL_Surface* tempSurface = IMG_Load(filename.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    return texture;
}

SDL_Texture* Image::getTexture() {
    return texture;
}
