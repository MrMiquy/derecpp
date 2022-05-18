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

void Image::setPosition(SDL_Point position) {
    geometry.x = position.x;
    geometry.y = position.y;
}

void Image::setSize(SDL_Point _size) {
    geometry.w = _size.x;
    geometry.h = _size.y;
}

SDL_Point Image::getPosition() {
    return {geometry.x, geometry.y};
}

SDL_Point Image::getSize() {
    return {geometry.w, geometry.h};
}

SDL_Texture* Image::getTexture() {
    return texture;
}
