#include "../headers/Label.h"

Label::Label() {
}

Label::~Label() {
    TTF_CloseFont(font);
    SDL_DestroyTexture(texture);
}

void Label::render() {
    Widget::render();
    applyTexture();

    SDL_RenderCopy(renderer, texture, NULL, &geometry);
}

void Label::setRenderer(SDL_Renderer* _renderer) {
    Widget::setRenderer(_renderer);

    TTF_SizeText(font, text.c_str(), &geometry.w, &geometry.h);
}

void Label::setText(std::string _text) {
    text = _text;
    if (font) {
        TTF_SizeText(font, text.c_str(), &geometry.w, &geometry.h);
    }
}

void Label::setFont(std::string fontname, int fontsize) {
    font = TTF_OpenFont(fontname.c_str(), fontsize);
}

void Label::applyTexture() {
    SDL_Surface* surfaceText = TTF_RenderText_Blended(font, text.c_str(), getColorByState(getMouseState()));

    texture = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_FreeSurface(surfaceText);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(texture, getColorByState(getMouseState()).a);
}

std::string Label::getText() {
    return text;
}
