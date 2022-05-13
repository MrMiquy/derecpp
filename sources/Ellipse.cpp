#include "../headers/Ellipse.h"

Ellipse::Ellipse() {
}

Ellipse::~Ellipse() {
}

void Ellipse::render() {
    geometry.x += geometry.w / 2;
    geometry.y += geometry.h / 2;
    const float pi = 3.1415926535897932384626433832795028841971693993751;
    const float pih = pi / 2.0;

    const int prec = 7;
    float theta = 0;

    int x = (float)geometry.w * cos(theta);
    int y = (float)geometry.h * sin(theta);
    int x1 = x;
    int y1 = y;

    float step = pih / (float)prec;
    if (ms == mouseNone) {
        SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    } else if (ms == mouseHover) {
        SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    } else if (ms == mousePressed) {
        SDL_SetRenderDrawColor(renderer, pressedColor.r, pressedColor.g, pressedColor.b, pressedColor.a);
    }

    for (theta = step; theta <= pih; theta += step) {
        x1 = (float)geometry.w * cosf(theta) + 0.5;
        y1 = (float)geometry.h * sinf(theta) + 0.5;

        if ( (x != x1) || (y != y1) ) {
            SDL_RenderDrawLine(renderer, geometry.x + x, geometry.y - y,    geometry.x + x1, geometry.y - y1);
            SDL_RenderDrawLine(renderer, geometry.x - x, geometry.y - y,    geometry.x - x1, geometry.y - y1);
            //SDL_RenderDrawLine(renderer, geometry.x - x, geometry.y + y,    geometry.x - x1, geometry.y + y1);
            //SDL_RenderDrawLine(renderer, geometry.x + x, geometry.y + y,    geometry.x + x1, geometry.y + y1);
        }
        x = x1;
        y = y1;
    }

    if (x != 0) {
        x = 0;
        SDL_RenderDrawLine(renderer, geometry.x + x, geometry.y - y,    geometry.x + x1, geometry.y - y1);
        SDL_RenderDrawLine(renderer, geometry.x - x, geometry.y - y,    geometry.x - x1, geometry.y - y1);
        SDL_RenderDrawLine(renderer, geometry.x - x, geometry.y + y,    geometry.x - x1, geometry.y + y1);
        SDL_RenderDrawLine(renderer, geometry.x + x, geometry.y + y,    geometry.x + x1, geometry.y + y1);
    }
    geometry.x -= geometry.w / 2;
    geometry.y -= geometry.h / 2;
}
