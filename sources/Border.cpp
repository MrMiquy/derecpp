#include "../headers/Border.h"

Border::Border() {
}

Border::~Border() {
}

void Border::render() {
    if (enable) {
        if (ms == mouseNone) {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        } else if (ms == mouseHover) {
            SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        } else if (ms == mousePressed) {
            SDL_SetRenderDrawColor(renderer, pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
        }
        SDL_RenderFillRect(renderer, &geometry);
    }
}
