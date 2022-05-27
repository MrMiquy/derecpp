#include "../headers/Border.h"

Border::Border() {
}

Border::~Border() {
}

void Border::render() {
    if (enable) {
        SDL_Rect temp = {0, 0, geometry.w, geometry.h};
        SDL_Texture* auxtexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, geometry.w, geometry.h);
        SDL_SetTextureBlendMode(auxtexture, SDL_BLENDMODE_BLEND);

        if (ms == mouseNone || useColorize == false) {
            SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
        } else if (ms == mouseHover) {
            SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
        } else if (ms == mousePressed) {
            SDL_SetRenderDrawColor(renderer, pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
        }

        SDL_SetRenderTarget(renderer, auxtexture);


        SDL_RenderFillRect(renderer, &temp);

        for (Widget* child : children) {
            child->setGeometry({child->getGeometry().x - geometry.x, child->getGeometry().y - geometry.y, child->getGeometry().w, child->getGeometry().h});
            child->render();
            child->setGeometry({child->getGeometry().x + geometry.x, child->getGeometry().y + geometry.y, child->getGeometry().w, child->getGeometry().h});
        }

        SDL_SetRenderTarget(renderer, NULL);
        SDL_RenderCopy(renderer, auxtexture, NULL, &geometry);
        SDL_DestroyTexture(auxtexture);
    }
}
